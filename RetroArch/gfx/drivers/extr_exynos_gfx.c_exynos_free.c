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
struct exynos_data {int /*<<< orphan*/ * device; int /*<<< orphan*/ ** buf; int /*<<< orphan*/ * pages; int /*<<< orphan*/  num_pages; } ;

/* Variables and functions */
 unsigned int EXYNOS_BUFFER_COUNT ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ drmModeSetCrtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_bo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_clean_up_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_device_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_crtc_id ; 
 int /*<<< orphan*/  g_drm_fd ; 

__attribute__((used)) static void exynos_free(struct exynos_data *pdata)
{
   unsigned i;

   /* Disable the CRTC. */
   if (drmModeSetCrtc(g_drm_fd, g_crtc_id, 0,
            0, 0, NULL, 0, NULL))
      RARCH_WARN("[video_exynos]: failed to disable the CRTC.\n");

   exynos_clean_up_pages(pdata->pages, pdata->num_pages);

   free(pdata->pages);
   pdata->pages = NULL;

   for (i = 0; i < EXYNOS_BUFFER_COUNT; ++i)
   {
      exynos_bo_destroy(pdata->buf[i]);
      pdata->buf[i] = NULL;
   }

   exynos_device_destroy(pdata->device);
   pdata->device = NULL;
}