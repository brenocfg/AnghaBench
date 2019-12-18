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
struct xenfb_info {TYPE_1__* page; int /*<<< orphan*/  feature_resize; } ;
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; int xres_virtual; int yres_virtual; } ;
struct TYPE_4__ {int line_length; int smem_len; } ;
struct fb_info {TYPE_2__ fix; struct xenfb_info* par; } ;
struct TYPE_3__ {int depth; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t KPARAM_HEIGHT ; 
 size_t KPARAM_WIDTH ; 
 int XENFB_DEPTH ; 
 int* video ; 

__attribute__((used)) static int
xenfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct xenfb_info *xenfb_info;
	int required_mem_len;

	xenfb_info = info->par;

	if (!xenfb_info->feature_resize) {
		if (var->xres == video[KPARAM_WIDTH] &&
		    var->yres == video[KPARAM_HEIGHT] &&
		    var->bits_per_pixel == xenfb_info->page->depth) {
			return 0;
		}
		return -EINVAL;
	}

	/* Can't resize past initial width and height */
	if (var->xres > video[KPARAM_WIDTH] || var->yres > video[KPARAM_HEIGHT])
		return -EINVAL;

	required_mem_len = var->xres * var->yres * xenfb_info->page->depth / 8;
	if (var->bits_per_pixel == xenfb_info->page->depth &&
	    var->xres <= info->fix.line_length / (XENFB_DEPTH / 8) &&
	    required_mem_len <= info->fix.smem_len) {
		var->xres_virtual = var->xres;
		var->yres_virtual = var->yres;
		return 0;
	}
	return -EINVAL;
}