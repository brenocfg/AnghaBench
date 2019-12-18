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
 int vc_api ; 

__attribute__((used)) static bool gfx_ctx_vc_bind_api(void *data,
      enum gfx_ctx_api api, unsigned major, unsigned minor)
{
   (void)data;
   (void)major;
   (void)minor;

   vc_api = api;

   switch (api)
   {
      case GFX_CTX_OPENGL_API:
         return eglBindAPI(EGL_OPENGL_API);
      case GFX_CTX_OPENGL_ES_API:
         return eglBindAPI(EGL_OPENGL_ES_API);
      case GFX_CTX_OPENVG_API:
         return eglBindAPI(EGL_OPENVG_API);
      default:
         break;
   }

   return false;
}