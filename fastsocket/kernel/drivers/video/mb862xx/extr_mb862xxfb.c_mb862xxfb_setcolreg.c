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
struct mb862xxfb_par {unsigned int* pseudo_palette; } ;
struct TYPE_4__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_3__ {int visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct mb862xxfb_par* par; } ;

/* Variables and functions */
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 int /*<<< orphan*/  GC_L0PAL0 ; 
 unsigned int chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disp ; 
 int /*<<< orphan*/  outreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mb862xxfb_setcolreg(unsigned regno,
			       unsigned red, unsigned green, unsigned blue,
			       unsigned transp, struct fb_info *info)
{
	struct mb862xxfb_par *par = info->par;
	unsigned int val;

	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		if (regno < 16) {
			val  = chan_to_field(red,   &info->var.red);
			val |= chan_to_field(green, &info->var.green);
			val |= chan_to_field(blue,  &info->var.blue);
			par->pseudo_palette[regno] = val;
		}
		break;
	case FB_VISUAL_PSEUDOCOLOR:
		if (regno < 256) {
			val = (red >> 8) << 16;
			val |= (green >> 8) << 8;
			val |= blue >> 8;
			outreg(disp, GC_L0PAL0 + (regno * 4), val);
		}
		break;
	default:
		return 1;   /* unsupported type */
	}
	return 0;
}