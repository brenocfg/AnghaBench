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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  au1200_setpanel (int /*<<< orphan*/ *) ; 
 scalar_t__ noblanking ; 
 int /*<<< orphan*/ * panel ; 

__attribute__((used)) static int au1200fb_fb_blank(int blank_mode, struct fb_info *fbi)
{
	/* Short-circuit screen blanking */
	if (noblanking)
		return 0;

	switch (blank_mode) {

	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		/* printk("turn on panel\n"); */
		au1200_setpanel(panel);
		break;
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_POWERDOWN:
		/* printk("turn off panel\n"); */
		au1200_setpanel(NULL);
		break;
	default:
		break;

	}

	/* FB_BLANK_NORMAL is a soft blank */
	return (blank_mode == FB_BLANK_NORMAL) ? -EINVAL : 0;
}