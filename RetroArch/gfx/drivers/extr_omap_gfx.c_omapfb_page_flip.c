#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* old_page; TYPE_3__* current_state; int /*<<< orphan*/  fd; TYPE_2__* cur_page; scalar_t__ sync; } ;
typedef  TYPE_5__ omapfb_data_t ;
struct TYPE_10__ {int /*<<< orphan*/  yoffset; } ;
struct TYPE_9__ {TYPE_4__ si; } ;
struct TYPE_8__ {int /*<<< orphan*/  yoffset; } ;
struct TYPE_7__ {int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOPAN_DISPLAY ; 
 int /*<<< orphan*/  OMAPFB_WAITFORGO ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void omapfb_page_flip(omapfb_data_t *pdata)
{
   if (pdata->sync)
      ioctl(pdata->fd, OMAPFB_WAITFORGO);

   /* TODO: should we use the manual update feature of the OMAP here? */

   pdata->current_state->si.yoffset = pdata->cur_page->yoffset;
   ioctl(pdata->fd, FBIOPAN_DISPLAY, &pdata->current_state->si);

   if (pdata->old_page)
      pdata->old_page->used = false;
}