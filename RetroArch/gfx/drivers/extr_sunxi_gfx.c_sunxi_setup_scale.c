#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sunxi_video {unsigned int src_width; unsigned int src_height; unsigned int src_pitch; int src_pixels_per_line; int bytes_per_pixel; int dst_pitch; unsigned int aspect_ratio; TYPE_2__* sunxi_disp; TYPE_1__* pages; } ;
struct TYPE_5__ {int yres; int xres; scalar_t__ framebuffer_addr; } ;
struct TYPE_4__ {int offset; int /*<<< orphan*/ * address; } ;

/* Variables and functions */
 int NUMPAGES ; 
 int /*<<< orphan*/  sunxi_layer_set_output_window (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sunxi_layer_show (TYPE_2__*) ; 

__attribute__((used)) static void sunxi_setup_scale (void *data,
      unsigned width, unsigned height, unsigned pitch)
{
   int i;
   unsigned int xpos, visible_width;
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;

   _dispvars->src_width  = width;
   _dispvars->src_height = height;

   /* Total pitch, including things the
    * cores render between "visible" scanlines. */
   _dispvars->src_pitch = pitch;

   /* Pixels per line */
   _dispvars->src_pixels_per_line = _dispvars->src_pitch/_dispvars->bytes_per_pixel;

   /* Incremental offset that sums up on
    * each previous page offset.
    * Total offset of each page has to
    * be adjusted when internal resolution changes. */
   for (i = 0; i < NUMPAGES; i++)
   {
      _dispvars->pages[i].offset = (_dispvars->sunxi_disp->yres + i * _dispvars->src_height) * _dispvars->sunxi_disp->xres * 4;
      _dispvars->pages[i].address = ((uint32_t*) _dispvars->sunxi_disp->framebuffer_addr + (_dispvars->sunxi_disp->yres + i * _dispvars->src_height) * _dispvars->dst_pitch/4);
   }

   visible_width = _dispvars->sunxi_disp->yres * _dispvars->aspect_ratio;
   xpos = (_dispvars->sunxi_disp->xres - visible_width) / 2;

   /* setup layer window */
   sunxi_layer_set_output_window(_dispvars->sunxi_disp, xpos, 0, visible_width, _dispvars->sunxi_disp->yres);

   /* make the layer visible */
   sunxi_layer_show(_dispvars->sunxi_disp);
}