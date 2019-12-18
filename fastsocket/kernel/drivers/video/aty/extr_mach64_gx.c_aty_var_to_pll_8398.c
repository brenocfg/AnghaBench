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
struct TYPE_2__ {int program_bits; int period_in_ps; scalar_t__ post_divider; scalar_t__ locationAddr; } ;
union aty_pll {TYPE_1__ ics2595; } ;
typedef  int u32 ;
typedef  int u16 ;
struct fb_info {int dummy; } ;
typedef  int save_m ;

/* Variables and functions */
 int MAX_FREQ_2595 ; 
 int MAX_M ; 
 int MAX_N ; 
 int MIN_FREQ_2595 ; 
 int MIN_M ; 
 int MIN_N ; 
 int REF_FREQ_2595 ; 

__attribute__((used)) static int aty_var_to_pll_8398(const struct fb_info *info, u32 vclk_per,
			       u32 bpp, union aty_pll *pll)
{
	u32 tempA, tempB, fOut, longMHz100, diff, preDiff;

	u32 mhz100;		/* in 0.01 MHz */
	u32 program_bits;
	/* u32 post_divider; */
	u32 mach64MinFreq, mach64MaxFreq, mach64RefFreq;
	u16 m, n, k = 0, save_m, save_n, twoToKth;

	/* Calculate the programming word */
	mhz100 = 100000000 / vclk_per;
	mach64MinFreq = MIN_FREQ_2595;
	mach64MaxFreq = MAX_FREQ_2595;
	mach64RefFreq = REF_FREQ_2595;	/* 14.32 MHz */

	save_m = 0;
	save_n = 0;

	/* Calculate program word */
	if (mhz100 == 0)
		program_bits = 0xE0;
	else {
		if (mhz100 < mach64MinFreq)
			mhz100 = mach64MinFreq;
		if (mhz100 > mach64MaxFreq)
			mhz100 = mach64MaxFreq;

		longMHz100 = mhz100 * 256 / 100;	/* 8 bit scale this */

		while (mhz100 < (mach64MinFreq << 3)) {
			mhz100 <<= 1;
			k++;
		}

		twoToKth = 1 << k;
		diff = 0;
		preDiff = 0xFFFFFFFF;

		for (m = MIN_M; m <= MAX_M; m++) {
			for (n = MIN_N; n <= MAX_N; n++) {
				tempA = 938356;		/* 14.31818 * 65536 */
				tempA *= (n + 8);	/* 43..256 */
				tempB = twoToKth * 256;
				tempB *= (m + 2);	/* 4..32 */
				fOut = tempA / tempB;	/* 8 bit scale */

				if (longMHz100 > fOut)
					diff = longMHz100 - fOut;
				else
					diff = fOut - longMHz100;

				if (diff < preDiff) {
					save_m = m;
					save_n = n;
					preDiff = diff;
				}
			}
		}

		program_bits = (k << 6) + (save_m) + (save_n << 8);
	}

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_divider = 0;
	pll->ics2595.period_in_ps = vclk_per;

	return 0;
}