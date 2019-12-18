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
struct mfb_info {int blank; } ;
struct fb_info {struct mfb_info* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 

__attribute__((used)) static int fsl_diu_blank(int blank_mode, struct fb_info *info)
{
	struct mfb_info *mfbi = info->par;

	mfbi->blank = blank_mode;

	switch (blank_mode) {
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	/* FIXME: fixes to enable_panel and enable lcdc needed */
	case FB_BLANK_NORMAL:
	/*	fsl_diu_disable_panel(info);*/
		break;
	case FB_BLANK_POWERDOWN:
	/*	disable_lcdc(info);	*/
		break;
	case FB_BLANK_UNBLANK:
	/*	fsl_diu_enable_panel(info);*/
		break;
	}

	return 0;
}