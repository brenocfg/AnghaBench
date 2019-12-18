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
struct exynos_video {int /*<<< orphan*/ * font; TYPE_1__* font_driver; int /*<<< orphan*/  perf; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; struct exynos_video* data; } ;
struct exynos_data {int /*<<< orphan*/ * font; TYPE_1__* font_driver; int /*<<< orphan*/  perf; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; struct exynos_data* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_wait_flip (int) ; 
 int /*<<< orphan*/  exynos_close (struct exynos_video*) ; 
 int /*<<< orphan*/  exynos_deinit (struct exynos_video*) ; 
 int /*<<< orphan*/  exynos_free (struct exynos_video*) ; 
 int /*<<< orphan*/  exynos_g2d_free (struct exynos_video*) ; 
 int exynos_pages_used (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_perf_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct exynos_video*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exynos_gfx_free(void *data)
{
   struct exynos_video *vid = data;
   struct exynos_data *pdata;

   if (!vid)
      return;

   pdata = vid->data;

   exynos_g2d_free(pdata);

   /* Flush pages: One page remains, the one being displayed at this moment. */
   while (exynos_pages_used(pdata->pages, pdata->num_pages) > 1)
      drm_wait_flip(-1);

   exynos_free(pdata);
   exynos_deinit(pdata);
   exynos_close(pdata);

#if (EXYNOS_GFX_DEBUG_PERF == 1)
   exynos_perf_finish(&pdata->perf);
#endif

   free(pdata);

   if (vid->font != NULL && vid->font_driver != NULL)
      vid->font_driver->free(vid->font);

   free(vid);
}