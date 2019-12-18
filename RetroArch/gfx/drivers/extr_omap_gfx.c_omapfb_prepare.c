#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int used; } ;
typedef  TYPE_1__ omapfb_page_t ;
struct TYPE_8__ {TYPE_1__* cur_page; TYPE_1__* old_page; } ;
typedef  TYPE_2__ omapfb_data_t ;

/* Variables and functions */
 TYPE_1__* omapfb_get_page (TYPE_2__*) ; 
 int /*<<< orphan*/  omapfb_page_flip (TYPE_2__*) ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omapfb_prepare(omapfb_data_t *pdata)
{
   omapfb_page_t *page = NULL;

   /* issue flip before getting free page */
   omapfb_page_flip(pdata);

   page            = omapfb_get_page(pdata);

   retro_assert(page != NULL);

   pdata->old_page = pdata->cur_page;
   pdata->cur_page = page;

   pdata->cur_page->used = true;
}