#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mx3fb_info {int blank; struct mx3fb_data* mx3fb; } ;
struct mx3fb_data {int /*<<< orphan*/  backlight_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ screen_base; struct mx3fb_info* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sdc_disable_channel (struct mx3fb_info*) ; 
 int /*<<< orphan*/  sdc_enable_channel (struct mx3fb_info*) ; 
 int /*<<< orphan*/  sdc_set_brightness (struct mx3fb_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __blank(int blank, struct fb_info *fbi)
{
	struct mx3fb_info *mx3_fbi = fbi->par;
	struct mx3fb_data *mx3fb = mx3_fbi->mx3fb;

	mx3_fbi->blank = blank;

	switch (blank) {
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
		sdc_set_brightness(mx3fb, 0);
		memset((char *)fbi->screen_base, 0, fbi->fix.smem_len);
		/* Give LCD time to update - enough for 50 and 60 Hz */
		msleep(25);
		sdc_disable_channel(mx3_fbi);
		break;
	case FB_BLANK_UNBLANK:
		sdc_enable_channel(mx3_fbi);
		sdc_set_brightness(mx3fb, mx3fb->backlight_level);
		break;
	}
}