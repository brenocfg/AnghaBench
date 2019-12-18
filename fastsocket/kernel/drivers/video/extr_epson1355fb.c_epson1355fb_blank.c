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
struct fb_info {struct epson1355_par* par; } ;
struct epson1355_par {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  backlight_enable (int) ; 
 int /*<<< orphan*/  lcd_enable (struct epson1355_par*,int) ; 

__attribute__((used)) static int epson1355fb_blank(int blank_mode, struct fb_info *info)
{
	struct epson1355_par *par = info->par;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		lcd_enable(par, 1);
		backlight_enable(1);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
		backlight_enable(0);
		break;
	case FB_BLANK_POWERDOWN:
		backlight_enable(0);
		lcd_enable(par, 0);
		break;
	default:
		return -EINVAL;
	}

	/* let fbcon do a soft blank for us */
	return (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
}