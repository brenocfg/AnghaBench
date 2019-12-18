#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct w100_pll_info {int dummy; } ;
struct TYPE_4__ {int pll_dactal; int pll_tcpoff; } ;
struct TYPE_5__ {scalar_t__ val; TYPE_1__ f; } ;
struct TYPE_6__ {TYPE_2__ pll_cntl; } ;

/* Variables and functions */
 scalar_t__ mmPLL_CNTL ; 
 scalar_t__ remapped_regs ; 
 int /*<<< orphan*/  udelay (int) ; 
 int w100_pll_adjust (struct w100_pll_info*) ; 
 TYPE_3__ w100_pwr_state ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int w100_pll_calibration(struct w100_pll_info *pll)
{
	int status;

	status = w100_pll_adjust(pll);

	/* PLL Reset And Lock */
	/* set VCO input = 0.5 * VDD */
	w100_pwr_state.pll_cntl.f.pll_dactal = 0xa;
	writel((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	udelay(1);  /* reset time */

	/* enable charge pump */
	w100_pwr_state.pll_cntl.f.pll_tcpoff = 0x0;  /* normal */
	writel((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	/* set VCO input = Hi-Z, disable DAC */
	w100_pwr_state.pll_cntl.f.pll_dactal = 0x0;
	writel((u32) (w100_pwr_state.pll_cntl.val), remapped_regs + mmPLL_CNTL);

	udelay(400);  /* lock time */

	/* PLL locked */

	return status;
}