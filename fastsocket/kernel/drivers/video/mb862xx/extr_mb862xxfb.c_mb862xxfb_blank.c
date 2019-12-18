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
struct mb862xxfb_par {int dummy; } ;
struct fb_info {int /*<<< orphan*/  dev; struct mb862xxfb_par* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 unsigned long GC_DCM01_DEN ; 
 int /*<<< orphan*/  GC_DCM1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disp ; 
 unsigned long inreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mb862xxfb_blank(int mode, struct fb_info *fbi)
{
	struct mb862xxfb_par  *par = fbi->par;
	unsigned long reg;

	dev_dbg(fbi->dev, "blank mode=%d\n", mode);

	switch (mode) {
	case FB_BLANK_POWERDOWN:
		reg = inreg(disp, GC_DCM1);
		reg &= ~GC_DCM01_DEN;
		outreg(disp, GC_DCM1, reg);
		break;
	case FB_BLANK_UNBLANK:
		reg = inreg(disp, GC_DCM1);
		reg |= GC_DCM01_DEN;
		outreg(disp, GC_DCM1, reg);
		break;
	case FB_BLANK_NORMAL:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	default:
		return 1;
	}
	return 0;
}