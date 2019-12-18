#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fb_height; scalar_t__ fb_width; int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ gfx_ctx_drm_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_OPENVG_API 128 
 int drm_api ; 
 int /*<<< orphan*/  egl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_drm_resources (TYPE_1__*) ; 
 int /*<<< orphan*/ * g_bo ; 
 scalar_t__ g_connector_id ; 
 scalar_t__ g_crtc_id ; 
 int /*<<< orphan*/ * g_drm_mode ; 
 int /*<<< orphan*/ * g_next_bo ; 
 int /*<<< orphan*/  gfx_ctx_drm_wait_flip (int) ; 

__attribute__((used)) static void gfx_ctx_drm_destroy_resources(gfx_ctx_drm_data_t *drm)
{
   if (!drm)
      return;

   /* Make sure we acknowledge all page-flips. */
   gfx_ctx_drm_wait_flip(true);

   switch (drm_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         egl_destroy(&drm->egl);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   free_drm_resources(drm);

   g_drm_mode          = NULL;
   g_crtc_id           = 0;
   g_connector_id      = 0;

   drm->fb_width       = 0;
   drm->fb_height      = 0;

   g_bo                = NULL;
   g_next_bo           = NULL;
}