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
struct exynos_page {int /*<<< orphan*/  buf_id; } ;
struct exynos_data {scalar_t__ pageflip_pending; int /*<<< orphan*/  cur_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PAGE_FLIP_EVENT ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ drmModePageFlip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct exynos_page*) ; 
 int /*<<< orphan*/  drm_wait_flip (int) ; 
 int /*<<< orphan*/  g_crtc_id ; 
 int /*<<< orphan*/  g_drm_fd ; 

__attribute__((used)) static int exynos_flip(struct exynos_data *pdata, struct exynos_page *page)
{
   /* We don't queue multiple page flips. */
   if (pdata->pageflip_pending > 0)
      drm_wait_flip(-1);

   /* Issue a page flip at the next vblank interval. */
   if (drmModePageFlip(g_drm_fd, g_crtc_id, page->buf_id,
            DRM_MODE_PAGE_FLIP_EVENT, page) != 0)
   {
      RARCH_ERR("[video_exynos]: failed to issue page flip\n");
      return -1;
   }
   else
   {
      pdata->pageflip_pending++;
   }

   /* On startup no frame is displayed. We therefore wait for the initial flip to finish. */
   if (!pdata->cur_page)
      drm_wait_flip(-1);

   return 0;
}