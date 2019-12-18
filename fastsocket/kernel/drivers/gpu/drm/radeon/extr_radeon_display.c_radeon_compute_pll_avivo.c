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
struct radeon_pll {int min_ref_div; int flags; int reference_div; int reference_freq; int max_ref_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int,int) ; 
 int MAX_TOLERANCE ; 
 int RADEON_PLL_USE_FRAC_FB_DIV ; 
 int RADEON_PLL_USE_REF_DIV ; 
 int /*<<< orphan*/  avivo_get_fb_div (struct radeon_pll*,int,int,int,int*,int*) ; 
 int avivo_get_post_div (struct radeon_pll*,int) ; 

void radeon_compute_pll_avivo(struct radeon_pll *pll,
			      u32 freq,
			      u32 *dot_clock_p,
			      u32 *fb_div_p,
			      u32 *frac_fb_div_p,
			      u32 *ref_div_p,
			      u32 *post_div_p)
{
	u32 target_clock = freq / 10;
	u32 post_div = avivo_get_post_div(pll, target_clock);
	u32 ref_div = pll->min_ref_div;
	u32 fb_div = 0, frac_fb_div = 0, tmp;

	if (pll->flags & RADEON_PLL_USE_REF_DIV)
		ref_div = pll->reference_div;

	if (pll->flags & RADEON_PLL_USE_FRAC_FB_DIV) {
		avivo_get_fb_div(pll, target_clock, post_div, ref_div, &fb_div, &frac_fb_div);
		frac_fb_div = (100 * frac_fb_div) / pll->reference_freq;
		if (frac_fb_div >= 5) {
			frac_fb_div -= 5;
			frac_fb_div = frac_fb_div / 10;
			frac_fb_div++;
		}
		if (frac_fb_div >= 10) {
			fb_div++;
			frac_fb_div = 0;
		}
	} else {
		while (ref_div <= pll->max_ref_div) {
			avivo_get_fb_div(pll, target_clock, post_div, ref_div,
					 &fb_div, &frac_fb_div);
			if (frac_fb_div >= (pll->reference_freq / 2))
				fb_div++;
			frac_fb_div = 0;
			tmp = (pll->reference_freq * fb_div) / (post_div * ref_div);
			tmp = (tmp * 10000) / target_clock;

			if (tmp > (10000 + MAX_TOLERANCE))
				ref_div++;
			else if (tmp >= (10000 - MAX_TOLERANCE))
				break;
			else
				ref_div++;
		}
	}

	*dot_clock_p = ((pll->reference_freq * fb_div * 10) + (pll->reference_freq * frac_fb_div)) /
		(ref_div * post_div * 10);
	*fb_div_p = fb_div;
	*frac_fb_div_p = frac_fb_div;
	*ref_div_p = ref_div;
	*post_div_p = post_div;
	DRM_DEBUG_KMS("%d, pll dividers - fb: %d.%d ref: %d, post %d\n",
		      *dot_clock_p, fb_div, frac_fb_div, ref_div, post_div);
}