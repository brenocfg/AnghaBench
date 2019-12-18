#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int bpp; TYPE_3__* current_state; TYPE_1__* cur_page; } ;
typedef  TYPE_4__ omapfb_data_t ;
struct TYPE_7__ {unsigned int xres; } ;
struct TYPE_8__ {TYPE_2__ si; } ;
struct TYPE_6__ {void* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 

__attribute__((used)) static void omapfb_blit_frame(omapfb_data_t *pdata, const void *src,
      unsigned height, unsigned src_pitch)
{
   unsigned i;
   void          *dst = pdata->cur_page->buf;
   unsigned dst_pitch = pdata->current_state->si.xres * pdata->bpp;

   for (i = 0; i < height; i++)
      memcpy(dst + dst_pitch * i, src + src_pitch * i, dst_pitch);
}