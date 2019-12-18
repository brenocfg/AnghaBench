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
struct exynos_page {scalar_t__ used; } ;

/* Variables and functions */

__attribute__((used)) static unsigned exynos_pages_used(struct exynos_page *p, unsigned cnt)
{
   unsigned i;
   unsigned count = 0;

   for (i = 0; i < cnt; ++i)
   {
      if (p[i].used)
         ++count;
   }

   return count;
}