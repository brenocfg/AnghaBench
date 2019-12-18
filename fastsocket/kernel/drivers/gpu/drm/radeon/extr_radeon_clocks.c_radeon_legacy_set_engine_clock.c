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
typedef  int uint32_t ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CLK_PIN_CNTL ; 
 int RADEON_DONT_USE_XTALIN ; 
 int /*<<< orphan*/  RADEON_M_SPLL_REF_FB_DIV ; 
 int /*<<< orphan*/  RADEON_SCLK_CNTL ; 
 int RADEON_SCLK_SRC_SEL_MASK ; 
 int /*<<< orphan*/  RADEON_SPLL_CNTL ; 
 int RADEON_SPLL_FB_DIV_MASK ; 
 int RADEON_SPLL_FB_DIV_SHIFT ; 
 int RADEON_SPLL_PVG_MASK ; 
 int RADEON_SPLL_PVG_SHIFT ; 
 int RADEON_SPLL_RESET ; 
 int RADEON_SPLL_SLEEP ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int calc_eng_mem_clock (struct radeon_device*,int,int*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void radeon_legacy_set_engine_clock(struct radeon_device *rdev,
				    uint32_t eng_clock)
{
	uint32_t tmp;
	int fb_div, post_div;

	/* XXX: wait for idle */

	eng_clock = calc_eng_mem_clock(rdev, eng_clock, &fb_div, &post_div);

	tmp = RREG32_PLL(RADEON_CLK_PIN_CNTL);
	tmp &= ~RADEON_DONT_USE_XTALIN;
	WREG32_PLL(RADEON_CLK_PIN_CNTL, tmp);

	tmp = RREG32_PLL(RADEON_SCLK_CNTL);
	tmp &= ~RADEON_SCLK_SRC_SEL_MASK;
	WREG32_PLL(RADEON_SCLK_CNTL, tmp);

	udelay(10);

	tmp = RREG32_PLL(RADEON_SPLL_CNTL);
	tmp |= RADEON_SPLL_SLEEP;
	WREG32_PLL(RADEON_SPLL_CNTL, tmp);

	udelay(2);

	tmp = RREG32_PLL(RADEON_SPLL_CNTL);
	tmp |= RADEON_SPLL_RESET;
	WREG32_PLL(RADEON_SPLL_CNTL, tmp);

	udelay(200);

	tmp = RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV);
	tmp &= ~(RADEON_SPLL_FB_DIV_MASK << RADEON_SPLL_FB_DIV_SHIFT);
	tmp |= (fb_div & RADEON_SPLL_FB_DIV_MASK) << RADEON_SPLL_FB_DIV_SHIFT;
	WREG32_PLL(RADEON_M_SPLL_REF_FB_DIV, tmp);

	/* XXX: verify on different asics */
	tmp = RREG32_PLL(RADEON_SPLL_CNTL);
	tmp &= ~RADEON_SPLL_PVG_MASK;
	if ((eng_clock * post_div) >= 90000)
		tmp |= (0x7 << RADEON_SPLL_PVG_SHIFT);
	else
		tmp |= (0x4 << RADEON_SPLL_PVG_SHIFT);
	WREG32_PLL(RADEON_SPLL_CNTL, tmp);

	tmp = RREG32_PLL(RADEON_SPLL_CNTL);
	tmp &= ~RADEON_SPLL_SLEEP;
	WREG32_PLL(RADEON_SPLL_CNTL, tmp);

	udelay(2);

	tmp = RREG32_PLL(RADEON_SPLL_CNTL);
	tmp &= ~RADEON_SPLL_RESET;
	WREG32_PLL(RADEON_SPLL_CNTL, tmp);

	udelay(200);

	tmp = RREG32_PLL(RADEON_SCLK_CNTL);
	tmp &= ~RADEON_SCLK_SRC_SEL_MASK;
	switch (post_div) {
	case 1:
	default:
		tmp |= 1;
		break;
	case 2:
		tmp |= 2;
		break;
	case 4:
		tmp |= 3;
		break;
	case 8:
		tmp |= 4;
		break;
	}
	WREG32_PLL(RADEON_SCLK_CNTL, tmp);

	udelay(20);

	tmp = RREG32_PLL(RADEON_CLK_PIN_CNTL);
	tmp |= RADEON_DONT_USE_XTALIN;
	WREG32_PLL(RADEON_CLK_PIN_CNTL, tmp);

	udelay(10);
}