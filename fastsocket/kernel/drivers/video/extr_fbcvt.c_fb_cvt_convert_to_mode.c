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
struct fb_videomode {int sync; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  refresh; } ;
struct fb_cvt_data {int pixclock; int flags; int /*<<< orphan*/  vsync; int /*<<< orphan*/  v_front_porch; int /*<<< orphan*/  v_back_porch; int /*<<< orphan*/  hsync; int /*<<< orphan*/  h_front_porch; int /*<<< orphan*/  h_back_porch; int /*<<< orphan*/  f_refresh; } ;

/* Variables and functions */
 int FB_CVT_FLAG_REDUCED_BLANK ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  KHZ2PICOS (int) ; 

__attribute__((used)) static void fb_cvt_convert_to_mode(struct fb_cvt_data *cvt,
				   struct fb_videomode *mode)
{
	mode->refresh = cvt->f_refresh;
	mode->pixclock = KHZ2PICOS(cvt->pixclock/1000);
	mode->left_margin = cvt->h_back_porch;
	mode->right_margin = cvt->h_front_porch;
	mode->hsync_len = cvt->hsync;
	mode->upper_margin = cvt->v_back_porch;
	mode->lower_margin = cvt->v_front_porch;
	mode->vsync_len = cvt->vsync;

	mode->sync &= ~(FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT);

	if (cvt->flags & FB_CVT_FLAG_REDUCED_BLANK)
		mode->sync |= FB_SYNC_HOR_HIGH_ACT;
	else
		mode->sync |= FB_SYNC_VERT_HIGH_ACT;
}