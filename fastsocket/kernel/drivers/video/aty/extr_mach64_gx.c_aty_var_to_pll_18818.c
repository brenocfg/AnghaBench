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
struct TYPE_2__ {int program_bits; int post_divider; int period_in_ps; scalar_t__ locationAddr; } ;
union aty_pll {TYPE_1__ ics2595; } ;
typedef  int u32 ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int ABS_MIN_FREQ_2595 ; 
 int EINVAL ; 
 int MAX_FREQ_2595 ; 
 int MIN_FREQ_2595 ; 
 int N_ADJ_2595 ; 
 int REF_DIV_2595 ; 
 int REF_FREQ_2595 ; 
 int STOP_BITS_2595 ; 

__attribute__((used)) static int aty_var_to_pll_18818(const struct fb_info *info, u32 vclk_per,
				u32 bpp, union aty_pll *pll)
{
	u32 MHz100;		/* in 0.01 MHz */
	u32 program_bits;
	u32 post_divider;

	/* Calculate the programming word */
	MHz100 = 100000000 / vclk_per;

	program_bits = -1;
	post_divider = 1;

	if (MHz100 > MAX_FREQ_2595) {
		MHz100 = MAX_FREQ_2595;
		return -EINVAL;
	} else if (MHz100 < ABS_MIN_FREQ_2595) {
		program_bits = 0;	/* MHz100 = 257 */
		return -EINVAL;
	} else {
		while (MHz100 < MIN_FREQ_2595) {
			MHz100 *= 2;
			post_divider *= 2;
		}
	}
	MHz100 *= 1000;
	MHz100 = (REF_DIV_2595 * MHz100) / REF_FREQ_2595;
 
	MHz100 += 500;		/* + 0.5 round */
	MHz100 /= 1000;

	if (program_bits == -1) {
		program_bits = MHz100 - N_ADJ_2595;
		switch (post_divider) {
		case 1:
			program_bits |= 0x0600;
			break;
		case 2:
			program_bits |= 0x0400;
			break;
		case 4:
			program_bits |= 0x0200;
			break;
		case 8:
		default:
			break;
		}
	}

	program_bits |= STOP_BITS_2595;

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_divider = post_divider;
	pll->ics2595.period_in_ps = vclk_per;

	return 0;
}