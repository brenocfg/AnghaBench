#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int yoffset; int used; void* buf; } ;
typedef  TYPE_3__ omapfb_page_t ;
struct TYPE_10__ {int num_pages; int fb_framesize; TYPE_3__* cur_page; TYPE_3__* pages; int /*<<< orphan*/ * old_page; scalar_t__ fb_mem; TYPE_2__* current_state; } ;
typedef  TYPE_4__ omapfb_data_t ;
struct TYPE_7__ {int yres; } ;
struct TYPE_8__ {TYPE_1__ si; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omapfb_page_flip (TYPE_4__*) ; 

__attribute__((used)) static int omapfb_setup_pages(omapfb_data_t *pdata)
{
   int i;

   if (!pdata->pages)
   {
      pdata->pages = (omapfb_page_t*)calloc(pdata->num_pages, sizeof(omapfb_page_t));

      if (!pdata->pages)
      {
         RARCH_ERR("[video_omap]: pages allocation failed.\n");
         return -1;
      }
   }

   for (i = 0; i < pdata->num_pages; ++i)
   {
      pdata->pages[i].yoffset = i * pdata->current_state->si.yres;
      pdata->pages[i].buf     = (void*)((uint8_t*)pdata->fb_mem + (i * pdata->fb_framesize));
      pdata->pages[i].used    = false;
   }

   pdata->old_page = NULL;
   pdata->cur_page = &pdata->pages[0];

   memset(pdata->cur_page->buf, 0, pdata->fb_framesize);

   omapfb_page_flip(pdata);
   pdata->cur_page->used = true;

   return 0;
}