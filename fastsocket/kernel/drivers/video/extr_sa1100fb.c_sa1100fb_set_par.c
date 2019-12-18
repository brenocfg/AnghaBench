#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ visual; int line_length; } ;
struct TYPE_4__ {TYPE_1__ fix; } ;
struct sa1100fb_info {int palette_size; unsigned long map_cpu; TYPE_2__ fb; scalar_t__ map_dma; scalar_t__ palette_dma; int /*<<< orphan*/ * palette_cpu; int /*<<< orphan*/  cmap_static; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; } ;
struct fb_info {struct fb_var_screeninfo var; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 scalar_t__ FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ FB_VISUAL_STATIC_PSEUDOCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  sa1100fb_activate_var (struct fb_var_screeninfo*,struct sa1100fb_info*) ; 
 int /*<<< orphan*/  sa1100fb_set_truecolor (int) ; 

__attribute__((used)) static int sa1100fb_set_par(struct fb_info *info)
{
	struct sa1100fb_info *fbi = (struct sa1100fb_info *)info;
	struct fb_var_screeninfo *var = &info->var;
	unsigned long palette_mem_size;

	DPRINTK("set_par\n");

	if (var->bits_per_pixel == 16)
		fbi->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	else if (!fbi->cmap_static)
		fbi->fb.fix.visual = FB_VISUAL_PSEUDOCOLOR;
	else {
		/*
		 * Some people have weird ideas about wanting static
		 * pseudocolor maps.  I suspect their user space
		 * applications are broken.
		 */
		fbi->fb.fix.visual = FB_VISUAL_STATIC_PSEUDOCOLOR;
	}

	fbi->fb.fix.line_length = var->xres_virtual *
				  var->bits_per_pixel / 8;
	fbi->palette_size = var->bits_per_pixel == 8 ? 256 : 16;

	palette_mem_size = fbi->palette_size * sizeof(u16);

	DPRINTK("palette_mem_size = 0x%08lx\n", (u_long) palette_mem_size);

	fbi->palette_cpu = (u16 *)(fbi->map_cpu + PAGE_SIZE - palette_mem_size);
	fbi->palette_dma = fbi->map_dma + PAGE_SIZE - palette_mem_size;

	/*
	 * Set (any) board control register to handle new color depth
	 */
	sa1100fb_set_truecolor(fbi->fb.fix.visual == FB_VISUAL_TRUECOLOR);
	sa1100fb_activate_var(var, fbi);

	return 0;
}