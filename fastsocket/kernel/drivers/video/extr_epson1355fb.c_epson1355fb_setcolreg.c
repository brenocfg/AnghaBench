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
typedef  unsigned int u32 ;
struct TYPE_4__ {int visual; } ;
struct TYPE_3__ {scalar_t__ grayscale; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ fix; TYPE_1__ var; struct epson1355_par* par; } ;
struct epson1355_par {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 int /*<<< orphan*/  set_lut (struct epson1355_par*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int epson1355fb_setcolreg(unsigned regno, unsigned r, unsigned g,
				 unsigned b, unsigned transp,
				 struct fb_info *info)
{
	struct epson1355_par *par = info->par;

	if (info->var.grayscale)
		r = g = b = (19595 * r + 38470 * g + 7471 * b) >> 16;

	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		if (regno >= 16)
			return -EINVAL;

		((u32 *) info->pseudo_palette)[regno] =
		    (r & 0xf800) | (g & 0xfc00) >> 5 | (b & 0xf800) >> 11;

		break;
	case FB_VISUAL_PSEUDOCOLOR:
		if (regno >= 256)
			return -EINVAL;

		set_lut(par, regno, r >> 8, g >> 8, b >> 8);

		break;
	default:
		return -ENOSYS;
	}
	return 0;
}