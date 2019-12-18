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
struct exynos_page {scalar_t__ buf_id; TYPE_1__* bo; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeRmFB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_bo_destroy (TYPE_1__*) ; 

__attribute__((used)) static void exynos_clean_up_pages(struct exynos_page *p, unsigned cnt)
{
   unsigned i;

   for (i = 0; i < cnt; ++i)
   {
      if (p[i].bo != NULL)
      {
         if (p[i].buf_id != 0)
            drmModeRmFB(p[i].buf_id, p[i].bo->handle);

         exynos_bo_destroy(p[i].bo);
      }
   }
}