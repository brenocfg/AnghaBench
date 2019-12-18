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
struct radeon_pll {int flags; int post_div; int lcd_pll_out_min; int pll_out_min; int lcd_pll_out_max; int pll_out_max; int max_post_div; int min_post_div; } ;

/* Variables and functions */
 int RADEON_PLL_IS_LCD ; 
 int RADEON_PLL_PREFER_MINM_OVER_MAXP ; 
 int RADEON_PLL_USE_POST_DIV ; 

__attribute__((used)) static u32 avivo_get_post_div(struct radeon_pll *pll,
			      u32 target_clock)
{
	u32 vco, post_div, tmp;

	if (pll->flags & RADEON_PLL_USE_POST_DIV)
		return pll->post_div;

	if (pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP) {
		if (pll->flags & RADEON_PLL_IS_LCD)
			vco = pll->lcd_pll_out_min;
		else
			vco = pll->pll_out_min;
	} else {
		if (pll->flags & RADEON_PLL_IS_LCD)
			vco = pll->lcd_pll_out_max;
		else
			vco = pll->pll_out_max;
	}

	post_div = vco / target_clock;
	tmp = vco % target_clock;

	if (pll->flags & RADEON_PLL_PREFER_MINM_OVER_MAXP) {
		if (tmp)
			post_div++;
	} else {
		if (!tmp)
			post_div--;
	}

	if (post_div > pll->max_post_div)
		post_div = pll->max_post_div;
	else if (post_div < pll->min_post_div)
		post_div = pll->min_post_div;

	return post_div;
}