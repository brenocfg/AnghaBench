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
typedef  void* uint16_t ;
struct radeon_pll {int pll_in_min; int pll_in_max; void* pll_out_max; void* pll_out_min; void* reference_div; void* reference_freq; void* lcd_pll_out_max; void* lcd_pll_out_min; } ;
struct TYPE_2__ {int max_pixel_clock; void* default_mclk; void* default_sclk; struct radeon_pll mpll; struct radeon_pll spll; struct radeon_pll p2pll; struct radeon_pll p1pll; } ;
struct radeon_device {TYPE_1__ clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_PLL_INFO_TABLE ; 
 void* RBIOS16 (void*) ; 
 void* RBIOS32 (void*) ; 
 int RBIOS8 (void*) ; 
 void* combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 

bool radeon_combios_get_clock_info(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	uint16_t pll_info;
	struct radeon_pll *p1pll = &rdev->clock.p1pll;
	struct radeon_pll *p2pll = &rdev->clock.p2pll;
	struct radeon_pll *spll = &rdev->clock.spll;
	struct radeon_pll *mpll = &rdev->clock.mpll;
	int8_t rev;
	uint16_t sclk, mclk;

	pll_info = combios_get_table_offset(dev, COMBIOS_PLL_INFO_TABLE);
	if (pll_info) {
		rev = RBIOS8(pll_info);

		/* pixel clocks */
		p1pll->reference_freq = RBIOS16(pll_info + 0xe);
		p1pll->reference_div = RBIOS16(pll_info + 0x10);
		p1pll->pll_out_min = RBIOS32(pll_info + 0x12);
		p1pll->pll_out_max = RBIOS32(pll_info + 0x16);
		p1pll->lcd_pll_out_min = p1pll->pll_out_min;
		p1pll->lcd_pll_out_max = p1pll->pll_out_max;

		if (rev > 9) {
			p1pll->pll_in_min = RBIOS32(pll_info + 0x36);
			p1pll->pll_in_max = RBIOS32(pll_info + 0x3a);
		} else {
			p1pll->pll_in_min = 40;
			p1pll->pll_in_max = 500;
		}
		*p2pll = *p1pll;

		/* system clock */
		spll->reference_freq = RBIOS16(pll_info + 0x1a);
		spll->reference_div = RBIOS16(pll_info + 0x1c);
		spll->pll_out_min = RBIOS32(pll_info + 0x1e);
		spll->pll_out_max = RBIOS32(pll_info + 0x22);

		if (rev > 10) {
			spll->pll_in_min = RBIOS32(pll_info + 0x48);
			spll->pll_in_max = RBIOS32(pll_info + 0x4c);
		} else {
			/* ??? */
			spll->pll_in_min = 40;
			spll->pll_in_max = 500;
		}

		/* memory clock */
		mpll->reference_freq = RBIOS16(pll_info + 0x26);
		mpll->reference_div = RBIOS16(pll_info + 0x28);
		mpll->pll_out_min = RBIOS32(pll_info + 0x2a);
		mpll->pll_out_max = RBIOS32(pll_info + 0x2e);

		if (rev > 10) {
			mpll->pll_in_min = RBIOS32(pll_info + 0x5a);
			mpll->pll_in_max = RBIOS32(pll_info + 0x5e);
		} else {
			/* ??? */
			mpll->pll_in_min = 40;
			mpll->pll_in_max = 500;
		}

		/* default sclk/mclk */
		sclk = RBIOS16(pll_info + 0xa);
		mclk = RBIOS16(pll_info + 0x8);
		if (sclk == 0)
			sclk = 200 * 100;
		if (mclk == 0)
			mclk = 200 * 100;

		rdev->clock.default_sclk = sclk;
		rdev->clock.default_mclk = mclk;

		if (RBIOS32(pll_info + 0x16))
			rdev->clock.max_pixel_clock = RBIOS32(pll_info + 0x16);
		else
			rdev->clock.max_pixel_clock = 35000; /* might need something asic specific */

		return true;
	}
	return false;
}