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
typedef  int u_int ;
struct sgivw_par {scalar_t__ cmap_fifo; TYPE_1__* regs; } ;
struct fb_info {scalar_t__ par; } ;
struct TYPE_2__ {scalar_t__ cm_fifo; int* cmap; } ;

/* Variables and functions */

__attribute__((used)) static int sgivwfb_setcolreg(u_int regno, u_int red, u_int green,
			     u_int blue, u_int transp,
			     struct fb_info *info)
{
	struct sgivw_par *par = (struct sgivw_par *) info->par;

	if (regno > 255)
		return 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	/* wait for the color map FIFO to have a free entry */
	while (par->cmap_fifo == 0)
		par->cmap_fifo = par->regs->cm_fifo;

	par->regs->cmap[regno] = (red << 24) | (green << 16) | (blue << 8);
	par->cmap_fifo--;	/* assume FIFO is filling up */
	return 0;
}