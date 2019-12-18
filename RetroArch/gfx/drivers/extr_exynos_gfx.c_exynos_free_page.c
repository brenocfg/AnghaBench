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
struct g2d_image {int /*<<< orphan*/ * bo; } ;
struct exynos_page {int clear; int used; TYPE_1__* bo; } ;
struct exynos_data {int /*<<< orphan*/  g2d; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; struct g2d_image* dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_wait_flip (int) ; 
 scalar_t__ exynos_clear_buffer (int /*<<< orphan*/ ,struct g2d_image*) ; 
 struct exynos_page* exynos_get_free_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct exynos_page *exynos_free_page(struct exynos_data *pdata)
{
   struct exynos_page *page = NULL;
   struct g2d_image *dst = pdata->dst;

   /* Wait until a free page is available. */
   while (!page)
   {
      page = exynos_get_free_page(pdata->pages, pdata->num_pages);

      if (!page)
         drm_wait_flip(-1);
   }

   dst->bo[0] = page->bo->handle;

   if (page->clear)
   {
      if (exynos_clear_buffer(pdata->g2d, dst) == 0)
         page->clear = false;
   }

   page->used = true;
   return page;
}