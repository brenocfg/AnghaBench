#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ gfx_ctx_drm_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_OPENVG_API 128 
 int drm_api ; 
 int /*<<< orphan*/  egl_bind_hw_render (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gfx_ctx_drm_bind_hw_render(void *data, bool enable)
{
   gfx_ctx_drm_data_t *drm     = (gfx_ctx_drm_data_t*)data;

   switch (drm_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         egl_bind_hw_render(&drm->egl, enable);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }
}