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
typedef  int u32 ;
struct radeon_pll {int reference_freq; int max_feedback_div; int min_feedback_div; } ;

/* Variables and functions */

__attribute__((used)) static void avivo_get_fb_div(struct radeon_pll *pll,
			     u32 target_clock,
			     u32 post_div,
			     u32 ref_div,
			     u32 *fb_div,
			     u32 *frac_fb_div)
{
	u32 tmp = post_div * ref_div;

	tmp *= target_clock;
	*fb_div = tmp / pll->reference_freq;
	*frac_fb_div = tmp % pll->reference_freq;

        if (*fb_div > pll->max_feedback_div)
		*fb_div = pll->max_feedback_div;
        else if (*fb_div < pll->min_feedback_div)
                *fb_div = pll->min_feedback_div;
}