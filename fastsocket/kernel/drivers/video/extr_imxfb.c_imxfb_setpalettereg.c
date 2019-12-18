#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct imxfb_info {int palette_size; scalar_t__ regs; } ;
struct fb_info {struct imxfb_info* par; } ;

/* Variables and functions */
 int CNVT_TOHW (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imxfb_setpalettereg(u_int regno, u_int red, u_int green, u_int blue,
		u_int trans, struct fb_info *info)
{
	struct imxfb_info *fbi = info->par;
	u_int val, ret = 1;

#define CNVT_TOHW(val,width) ((((val)<<(width))+0x7FFF-(val))>>16)
	if (regno < fbi->palette_size) {
		val = (CNVT_TOHW(red, 4) << 8) |
		      (CNVT_TOHW(green,4) << 4) |
		      CNVT_TOHW(blue,  4);

		writel(val, fbi->regs + 0x800 + (regno << 2));
		ret = 0;
	}
	return ret;
}