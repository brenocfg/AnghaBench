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
struct exynos_page {int used; TYPE_1__* base; } ;
struct TYPE_2__ {struct exynos_page* cur_page; int /*<<< orphan*/  pageflip_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,struct exynos_page*) ; 

__attribute__((used)) static void exynos_page_flip_handler(int fd, unsigned frame, unsigned sec,
      unsigned usec, void *data)
{
   struct exynos_page *page = data;

#if (EXYNOS_GFX_DEBUG_LOG == 1)
   RARCH_LOG("[video_exynos]: in exynos_page_flip_handler, page = %p\n", page);
#endif

   if (page->base->cur_page)
      page->base->cur_page->used = false;

   page->base->pageflip_pending--;
   page->base->cur_page = page;
}