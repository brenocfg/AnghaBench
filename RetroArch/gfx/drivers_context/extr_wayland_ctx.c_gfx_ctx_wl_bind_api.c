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
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_OPENGL_API ; 
 int /*<<< orphan*/  EGL_OPENGL_ES_API ; 
 int /*<<< orphan*/  EGL_OPENVG_API ; 
 int /*<<< orphan*/  EGL_TRUE ; 
#define  GFX_CTX_NONE 132 
#define  GFX_CTX_OPENGL_API 131 
#define  GFX_CTX_OPENGL_ES_API 130 
#define  GFX_CTX_OPENVG_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 unsigned int g_egl_major ; 
 unsigned int g_egl_minor ; 
 int wl_api ; 

__attribute__((used)) static bool gfx_ctx_wl_bind_api(void *video_driver,
      enum gfx_ctx_api api, unsigned major, unsigned minor)
{
#ifdef HAVE_EGL
   g_egl_major = major;
   g_egl_minor = minor;
#endif
   wl_api      = api;

   switch (api)
   {
      case GFX_CTX_OPENGL_API:
#ifdef HAVE_OPENGL
#ifndef EGL_KHR_create_context
         if ((major * 1000 + minor) >= 3001)
            return false;
#endif
#ifdef HAVE_EGL
         if (eglBindAPI(EGL_OPENGL_API) == EGL_TRUE)
            return true;
#endif
#endif
         break;
      case GFX_CTX_OPENGL_ES_API:
#ifdef HAVE_OPENGLES
#ifndef EGL_KHR_create_context
         if (major >= 3)
            return false;
#endif
#ifdef HAVE_EGL
         if (eglBindAPI(EGL_OPENGL_ES_API) == EGL_TRUE)
            return true;
#endif
#endif
         break;
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_VG
#ifdef HAVE_EGL
         if (eglBindAPI(EGL_OPENVG_API) == EGL_TRUE)
            return true;
#endif
#endif
         break;
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         return true;
#else
         break;
#endif
      case GFX_CTX_NONE:
      default:
         break;
   }

   return false;
}