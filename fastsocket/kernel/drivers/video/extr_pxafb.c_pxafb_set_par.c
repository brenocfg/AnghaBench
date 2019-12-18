#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int bits_per_pixel; } ;
struct TYPE_5__ {int line_length; int /*<<< orphan*/  visual; } ;
struct TYPE_8__ {TYPE_3__ var; int /*<<< orphan*/  cmap; TYPE_1__ fix; } ;
struct pxafb_info {int palette_size; TYPE_4__ fb; TYPE_2__* dma_buff; int /*<<< orphan*/ * palette_cpu; int /*<<< orphan*/  cmap_static; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; } ;
struct fb_info {struct fb_var_screeninfo var; } ;
struct TYPE_6__ {int /*<<< orphan*/ * palette; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_STATIC_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxafb_activate_var (struct fb_var_screeninfo*,struct pxafb_info*) ; 

__attribute__((used)) static int pxafb_set_par(struct fb_info *info)
{
	struct pxafb_info *fbi = (struct pxafb_info *)info;
	struct fb_var_screeninfo *var = &info->var;

	if (var->bits_per_pixel >= 16)
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
	if (var->bits_per_pixel >= 16)
		fbi->palette_size = 0;
	else
		fbi->palette_size = var->bits_per_pixel == 1 ?
					4 : 1 << var->bits_per_pixel;

	fbi->palette_cpu = (u16 *)&fbi->dma_buff->palette[0];

	if (fbi->fb.var.bits_per_pixel >= 16)
		fb_dealloc_cmap(&fbi->fb.cmap);
	else
		fb_alloc_cmap(&fbi->fb.cmap, 1<<fbi->fb.var.bits_per_pixel, 0);

	pxafb_activate_var(var, fbi);

	return 0;
}