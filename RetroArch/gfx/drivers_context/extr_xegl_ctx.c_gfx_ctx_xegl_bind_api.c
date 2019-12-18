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
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_OPENVG_API 128 
 int eglBindAPI (int /*<<< orphan*/ ) ; 
 unsigned int g_egl_major ; 
 unsigned int g_egl_minor ; 
 int xegl_api ; 

__attribute__((used)) static bool gfx_ctx_xegl_bind_api(void *video_driver,
   enum gfx_ctx_api api, unsigned major, unsigned minor)
{
   g_egl_major  = major;
   g_egl_minor  = minor;
   xegl_api     = api;

   switch (api)
   {
      case GFX_CTX_OPENGL_API:
#ifndef EGL_KHR_create_context
         if ((major * 1000 + minor) >= 3001)
            break;
#endif
         return eglBindAPI(EGL_OPENGL_API);
      case GFX_CTX_OPENGL_ES_API:
#ifndef EGL_KHR_create_context
         if (major >= 3)
            break;
#endif
         return eglBindAPI(EGL_OPENGL_ES_API);
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_VG
         return eglBindAPI(EGL_OPENVG_API);
#endif
      default:
         break;
   }

   return false;
}