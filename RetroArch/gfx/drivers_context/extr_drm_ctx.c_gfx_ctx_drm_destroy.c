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
typedef  int /*<<< orphan*/  gfx_ctx_drm_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_ctx_drm_destroy_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_ctx_drm_destroy(void *data)
{
   gfx_ctx_drm_data_t *drm = (gfx_ctx_drm_data_t*)data;

   if (!drm)
      return;

   gfx_ctx_drm_destroy_resources(drm);
   free(drm);
}