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
struct gbm_bo {int dummy; } ;
struct drm_fb {int /*<<< orphan*/  fb_id; struct gbm_bo* bo; } ;
struct TYPE_2__ {unsigned int u32; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ calloc (int,int) ; 
 int drmModeAddFB (int /*<<< orphan*/ ,unsigned int,unsigned int,int,int,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_destroy_callback ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct drm_fb*) ; 
 int /*<<< orphan*/  g_drm_fd ; 
 TYPE_1__ gbm_bo_get_handle (struct gbm_bo*) ; 
 unsigned int gbm_bo_get_height (struct gbm_bo*) ; 
 unsigned int gbm_bo_get_stride (struct gbm_bo*) ; 
 unsigned int gbm_bo_get_width (struct gbm_bo*) ; 
 int /*<<< orphan*/  gbm_bo_set_user_data (struct gbm_bo*,struct drm_fb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_fb *drm_fb_get_from_bo(struct gbm_bo *bo)
{
   int ret;
   unsigned width, height, stride, handle;
   struct drm_fb *fb = (struct drm_fb*)calloc(1, sizeof(*fb));

   fb->bo = bo;

   width  = gbm_bo_get_width(bo);
   height = gbm_bo_get_height(bo);
   stride = gbm_bo_get_stride(bo);
   handle = gbm_bo_get_handle(bo).u32;

   RARCH_LOG("[KMS]: New FB: %ux%u (stride: %u).\n",
         width, height, stride);

   ret = drmModeAddFB(g_drm_fd, width, height, 24, 32,
         stride, handle, &fb->fb_id);
   if (ret < 0)
      goto error;

   gbm_bo_set_user_data(bo, fb, drm_fb_destroy_callback);
   return fb;

error:
   RARCH_ERR("[KMS]: Failed to create FB: %s\n", strerror(errno));
   free(fb);
   return NULL;
}