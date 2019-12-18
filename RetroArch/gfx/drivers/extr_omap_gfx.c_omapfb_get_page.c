#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ omapfb_page_t ;
struct TYPE_6__ {unsigned int num_pages; TYPE_1__* pages; TYPE_1__* old_page; TYPE_1__* cur_page; } ;
typedef  TYPE_2__ omapfb_data_t ;

/* Variables and functions */

__attribute__((used)) static omapfb_page_t *omapfb_get_page(omapfb_data_t *pdata)
{
   unsigned i;
   omapfb_page_t *page = NULL;

   for (i = 0; i < pdata->num_pages; ++i)
   {
      if (&pdata->pages[i] == pdata->cur_page)
         continue;
      if (&pdata->pages[i] == pdata->old_page)
         continue;

      if (!pdata->pages[i].used)
      {
         page = &pdata->pages[i];
         break;
      }
   }

   return page;
}