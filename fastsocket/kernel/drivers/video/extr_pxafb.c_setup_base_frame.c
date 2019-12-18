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
struct fb_fix_screeninfo {int line_length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int yres; unsigned long yoffset; } ;
struct TYPE_2__ {struct fb_fix_screeninfo fix; struct fb_var_screeninfo var; } ;
struct pxafb_info {unsigned long video_mem_phys; int lccr0; TYPE_1__ fb; } ;

/* Variables and functions */
 int DMA_BASE ; 
 int DMA_MAX ; 
 int LCCR0_SDS ; 
 int PAL_BASE ; 
 int PAL_MAX ; 
 int PAL_NONE ; 
 int /*<<< orphan*/  setup_frame_dma (struct pxafb_info*,int,int,unsigned long,int) ; 

__attribute__((used)) static void setup_base_frame(struct pxafb_info *fbi, int branch)
{
	struct fb_var_screeninfo *var = &fbi->fb.var;
	struct fb_fix_screeninfo *fix = &fbi->fb.fix;
	int nbytes, dma, pal, bpp = var->bits_per_pixel;
	unsigned long offset;

	dma = DMA_BASE + (branch ? DMA_MAX : 0);
	pal = (bpp >= 16) ? PAL_NONE : PAL_BASE + (branch ? PAL_MAX : 0);

	nbytes = fix->line_length * var->yres;
	offset = fix->line_length * var->yoffset + fbi->video_mem_phys;

	if (fbi->lccr0 & LCCR0_SDS) {
		nbytes = nbytes / 2;
		setup_frame_dma(fbi, dma + 1, PAL_NONE, offset + nbytes, nbytes);
	}

	setup_frame_dma(fbi, dma, pal, offset, nbytes);
}