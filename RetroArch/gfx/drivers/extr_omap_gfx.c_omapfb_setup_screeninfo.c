#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int xres; int yres; int xres_virtual; int yres_virtual; int bits_per_pixel; scalar_t__ nonstd; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct TYPE_5__ {TYPE_4__ si; } ;
typedef  TYPE_1__ omapfb_state_t ;
struct TYPE_6__ {int num_pages; int bpp; int fb_framesize; int /*<<< orphan*/  fd; TYPE_1__* current_state; } ;
typedef  TYPE_2__ omapfb_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOPUT_VSCREENINFO ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int omapfb_setup_screeninfo(omapfb_data_t *pdata, int width, int height)
{
   omapfb_state_t* state    = pdata->current_state;

   state->si.xres           = width;
   state->si.yres           = height;
   state->si.xres_virtual   = width;
   state->si.yres_virtual   = height * pdata->num_pages;
   state->si.xoffset        = 0;
   state->si.yoffset        = 0;
   state->si.bits_per_pixel = pdata->bpp * 8;

   /* OMAPFB_COLOR_ARGB32 for bpp=4, OMAPFB_COLOR_RGB565 for bpp=2 */
   state->si.nonstd         = 0;

   if (ioctl(pdata->fd, FBIOPUT_VSCREENINFO, &state->si) != 0)
   {
      RARCH_ERR("[video_omap]: setup screeninfo failed\n");
      return -1;
   }

   pdata->fb_framesize      = width * height * pdata->bpp;

   return 0;
}