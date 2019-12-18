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
typedef  scalar_t__ (* pfn_eglGetPlatformDisplay ) (scalar_t__,void*,int /*<<< orphan*/ *) ;
typedef  scalar_t__ (* PFNEGLGETPLATFORMDISPLAYEXTPROC ) (scalar_t__,void*,int /*<<< orphan*/ *) ;
typedef  scalar_t__ EGLenum ;
typedef  int /*<<< orphan*/  EGLNativeDisplayType ;
typedef  scalar_t__ EGLDisplay ;
typedef  int /*<<< orphan*/  EGLAttrib ;

/* Variables and functions */
 scalar_t__ EGL_NONE ; 
 scalar_t__ EGL_NO_DISPLAY ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 scalar_t__ check_egl_client_extension (char*) ; 
 scalar_t__ check_egl_version (int,int) ; 
 scalar_t__ eglGetDisplay (int /*<<< orphan*/ ) ; 
 scalar_t__ eglGetProcAddress (char*) ; 

__attribute__((used)) static EGLDisplay get_egl_display(EGLenum platform, void *native)
{
   if (platform != EGL_NONE)
   {
      /* If the client library supports at least EGL 1.5, then we can call
       * eglGetPlatformDisplay. Otherwise, see if eglGetPlatformDisplayEXT
       * is available. */
#if defined(EGL_VERSION_1_5)
      if (check_egl_version(1, 5))
      {
         typedef EGLDisplay (EGLAPIENTRY * pfn_eglGetPlatformDisplay)
            (EGLenum platform, void *native_display, const EGLAttrib *attrib_list);
         pfn_eglGetPlatformDisplay ptr_eglGetPlatformDisplay;

         RARCH_LOG("[EGL] Found EGL client version >= 1.5, trying eglGetPlatformDisplay\n");
         ptr_eglGetPlatformDisplay = (pfn_eglGetPlatformDisplay)
            eglGetProcAddress("eglGetPlatformDisplay");
         if (ptr_eglGetPlatformDisplay != NULL)
         {
            EGLDisplay dpy = ptr_eglGetPlatformDisplay(platform, native, NULL);
            if (dpy != EGL_NO_DISPLAY)
               return dpy;
         }
      }
#endif /* defined(EGL_VERSION_1_5) */

#if defined(EGL_EXT_platform_base)
      if (check_egl_client_extension("EGL_EXT_platform_base"))
      {
         PFNEGLGETPLATFORMDISPLAYEXTPROC ptr_eglGetPlatformDisplayEXT;

         RARCH_LOG("[EGL] Found EGL_EXT_platform_base, trying eglGetPlatformDisplayEXT\n");
         ptr_eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)
            eglGetProcAddress("eglGetPlatformDisplayEXT");
         if (ptr_eglGetPlatformDisplayEXT != NULL)
         {
            EGLDisplay dpy = ptr_eglGetPlatformDisplayEXT(platform, native, NULL);
            if (dpy != EGL_NO_DISPLAY)
               return dpy;
         }
      }
#endif /* defined(EGL_EXT_platform_base) */
   }

   /* Either the caller didn't provide a platform type, or the EGL
    * implementation doesn't support eglGetPlatformDisplay. In this case, try
    * eglGetDisplay and hope for the best. */
   RARCH_LOG("[EGL] Falling back to eglGetDisplay\n");
   return eglGetDisplay((EGLNativeDisplayType) native);
}