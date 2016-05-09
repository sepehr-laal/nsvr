#pragma once

#include <string>
#include <gst/gst.h>
#include <gst/gstregistry.h>
#include <gst/app/gstappsink.h>
#include <gst/pbutils/gstdiscoverer.h>

namespace nsvr
{

template<typename T>
struct BindToScope
{
    BindToScope(T*& ptr) : pointer(ptr) {}
    ~BindToScope();
    T*& pointer;
};

template< class T > struct no_ptr        { typedef T type; };
template< class T > struct no_ptr<T*>    { typedef T type; };
#define BIND_TO_SCOPE(var) BindToScope<\
    no_ptr<decltype(var)>::type> scoped_##var(var);

class Discoverer;

class Internal
{
public:
    static bool         gstreamerInitialized();
    static void         reset(Discoverer& discoverer);
    static std::string  processPath(const std::string& path);
    static bool         isNullOrEmpty(const char* const str);
};

}
