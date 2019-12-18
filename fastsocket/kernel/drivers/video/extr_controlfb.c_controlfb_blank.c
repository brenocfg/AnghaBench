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
struct fb_info_control {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_REG (struct fb_info_control*,unsigned int) ; 
#define  FB_BLANK_HSYNC_SUSPEND 131 
#define  FB_BLANK_NORMAL 130 
#define  FB_BLANK_POWERDOWN 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 unsigned int ld_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int controlfb_blank(int blank_mode, struct fb_info *info)
{
	struct fb_info_control *p = (struct fb_info_control *) info;
	unsigned ctrl;

	ctrl = ld_le32(CNTRL_REG(p,ctrl));
	if (blank_mode > 0)
		switch (blank_mode) {
		case FB_BLANK_VSYNC_SUSPEND:
			ctrl &= ~3;
			break;
		case FB_BLANK_HSYNC_SUSPEND:
			ctrl &= ~0x30;
			break;
		case FB_BLANK_POWERDOWN:
			ctrl &= ~0x33;
			/* fall through */
		case FB_BLANK_NORMAL:
			ctrl |= 0x400;
			break;
		default:
			break;
		}
	else {
		ctrl &= ~0x400;
		ctrl |= 0x33;
	}
	out_le32(CNTRL_REG(p,ctrl), ctrl);

	return 0;
}