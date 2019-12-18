#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int EGLint ;

/* Variables and functions */
#define  EGL_BAD_ACCESS 142 
#define  EGL_BAD_ALLOC 141 
#define  EGL_BAD_ATTRIBUTE 140 
#define  EGL_BAD_CONFIG 139 
#define  EGL_BAD_CONTEXT 138 
#define  EGL_BAD_CURRENT_SURFACE 137 
#define  EGL_BAD_DISPLAY 136 
#define  EGL_BAD_MATCH 135 
#define  EGL_BAD_NATIVE_PIXMAP 134 
#define  EGL_BAD_NATIVE_WINDOW 133 
#define  EGL_BAD_PARAMETER 132 
#define  EGL_BAD_SURFACE 131 
#define  EGL_CONTEXT_LOST 130 
#define  EGL_NOT_INITIALIZED 129 
#define  EGL_SUCCESS 128 

__attribute__((used)) static const char* getErrorString(EGLint error)
{
    switch (error)
    {
        case EGL_SUCCESS:
            return "Success";
        case EGL_NOT_INITIALIZED:
            return "EGL is not or could not be initialized";
        case EGL_BAD_ACCESS:
            return "EGL cannot access a requested resource";
        case EGL_BAD_ALLOC:
            return "EGL failed to allocate resources for the requested operation";
        case EGL_BAD_ATTRIBUTE:
            return "An unrecognized attribute or attribute value was passed in the attribute list";
        case EGL_BAD_CONTEXT:
            return "An EGLContext argument does not name a valid EGL rendering context";
        case EGL_BAD_CONFIG:
            return "An EGLConfig argument does not name a valid EGL frame buffer configuration";
        case EGL_BAD_CURRENT_SURFACE:
            return "The current surface of the calling thread is a window, pixel buffer or pixmap that is no longer valid";
        case EGL_BAD_DISPLAY:
            return "An EGLDisplay argument does not name a valid EGL display connection";
        case EGL_BAD_SURFACE:
            return "An EGLSurface argument does not name a valid surface configured for GL rendering";
        case EGL_BAD_MATCH:
            return "Arguments are inconsistent";
        case EGL_BAD_PARAMETER:
            return "One or more argument values are invalid";
        case EGL_BAD_NATIVE_PIXMAP:
            return "A NativePixmapType argument does not refer to a valid native pixmap";
        case EGL_BAD_NATIVE_WINDOW:
            return "A NativeWindowType argument does not refer to a valid native window";
        case EGL_CONTEXT_LOST:
            return "The application must destroy all contexts and reinitialise";
    }

    return "UNKNOWN EGL ERROR";
}