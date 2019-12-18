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
struct omapfb_plane_struct {size_t idx; TYPE_2__* fbdev; } ;
struct omapfb_mem_region {int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; scalar_t__ nonstd; } ;
struct fb_fix_screeninfo {int line_length; int /*<<< orphan*/  accel; void* visual; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  screen_base; struct omapfb_plane_struct* par; struct fb_var_screeninfo var; struct fb_fix_screeninfo fix; } ;
struct TYPE_3__ {struct omapfb_mem_region* region; } ;
struct TYPE_4__ {TYPE_1__ mem_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_OMAP1610 ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_fb_fix(struct fb_info *fbi, int from_init)
{
	struct fb_fix_screeninfo *fix = &fbi->fix;
	struct fb_var_screeninfo *var = &fbi->var;
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_mem_region *rg;
	int bpp;

	rg = &plane->fbdev->mem_desc.region[plane->idx];
	fbi->screen_base	= rg->vaddr;

	if (!from_init) {
		mutex_lock(&fbi->mm_lock);
		fix->smem_start		= rg->paddr;
		fix->smem_len		= rg->size;
		mutex_unlock(&fbi->mm_lock);
	} else {
		fix->smem_start		= rg->paddr;
		fix->smem_len		= rg->size;
	}

	fix->type = FB_TYPE_PACKED_PIXELS;
	bpp = var->bits_per_pixel;
	if (var->nonstd)
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
	else switch (var->bits_per_pixel) {
	case 16:
	case 12:
		fix->visual = FB_VISUAL_TRUECOLOR;
		/* 12bpp is stored in 16 bits */
		bpp = 16;
		break;
	case 1:
	case 2:
	case 4:
	case 8:
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	}
	fix->accel		= FB_ACCEL_OMAP1610;
	fix->line_length	= var->xres_virtual * bpp / 8;
}