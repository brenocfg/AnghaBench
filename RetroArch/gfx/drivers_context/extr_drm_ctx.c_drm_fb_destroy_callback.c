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
struct gbm_bo {int dummy; } ;
struct drm_fb {scalar_t__ fb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeRmFB (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (struct drm_fb*) ; 
 int /*<<< orphan*/  g_drm_fd ; 

__attribute__((used)) static void drm_fb_destroy_callback(struct gbm_bo *bo, void *data)
{
   struct drm_fb *fb = (struct drm_fb*)data;

   if (fb && fb->fb_id)
      drmModeRmFB(g_drm_fd, fb->fb_id);

   free(fb);
}