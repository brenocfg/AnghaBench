#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fd; } ;
typedef  TYPE_1__ gfx_ctx_drm_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  drmDropMaster (int) ; 
 int /*<<< orphan*/  drm_free () ; 
 int /*<<< orphan*/  drm_restore_crtc () ; 
 int g_drm_fd ; 
 int /*<<< orphan*/ * g_gbm_dev ; 
 int /*<<< orphan*/ * g_gbm_surface ; 
 int /*<<< orphan*/  gbm_device_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gbm_surface_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_drm_resources(gfx_ctx_drm_data_t *drm)
{
   if (!drm)
      return;

   /* Restore original CRTC. */
   drm_restore_crtc();

   if (g_gbm_surface)
      gbm_surface_destroy(g_gbm_surface);

   if (g_gbm_dev)
      gbm_device_destroy(g_gbm_dev);

   drm_free();

   if (drm->fd >= 0)
   {
      if (g_drm_fd >= 0)
      {
         drmDropMaster(g_drm_fd);
         close(drm->fd);
      }
   }

   g_gbm_surface      = NULL;
   g_gbm_dev          = NULL;
   g_drm_fd           = -1;
}