#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int armBusRatio; int busClockFreqHz; int vpmBusRatio; int ddrBusRatio; int /*<<< orphan*/  pll2VcoFreqHz; int /*<<< orphan*/  ssSupport; int /*<<< orphan*/  pllVcoFreqHz; } ;
typedef  TYPE_1__ chipcHw_INIT_PARAM_t ;
struct TYPE_5__ {int ACLKClock; } ;

/* Variables and functions */
 int /*<<< orphan*/  chipcHw_CLOCK_ARM ; 
 int /*<<< orphan*/  chipcHw_CLOCK_BUS ; 
 int /*<<< orphan*/  chipcHw_CLOCK_DDR ; 
 int /*<<< orphan*/  chipcHw_CLOCK_RTBUS ; 
 int /*<<< orphan*/  chipcHw_CLOCK_VPM ; 
 int chipcHw_REG_ACLKClock_CLK_DIV_MASK ; 
 int chipcHw_REG_STICKY_CHIP_SOFT_RESET ; 
 int chipcHw_REG_STICKY_CHIP_WARM_RESET ; 
 int /*<<< orphan*/  chipcHw_clearStickyBits (int) ; 
 int chipcHw_getStickyBits () ; 
 int /*<<< orphan*/  chipcHw_pll1Enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipcHw_pll2Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipcHw_setClockFrequency (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  delay_init () ; 
 TYPE_2__* pChipcHw ; 

void chipcHw_Init(chipcHw_INIT_PARAM_t *initParam	/*  [ IN ] Misc chip initialization parameter */
    ) {
#if !(defined(__KERNEL__) && !defined(STANDALONE))
	delay_init();
#endif

	/* Do not program PLL, when warm reset */
	if (!(chipcHw_getStickyBits() & chipcHw_REG_STICKY_CHIP_WARM_RESET)) {
		chipcHw_pll1Enable(initParam->pllVcoFreqHz,
				   initParam->ssSupport);
		chipcHw_pll2Enable(initParam->pll2VcoFreqHz);
	} else {
		/* Clear sticky bits */
		chipcHw_clearStickyBits(chipcHw_REG_STICKY_CHIP_WARM_RESET);
	}
	/* Clear sticky bits */
	chipcHw_clearStickyBits(chipcHw_REG_STICKY_CHIP_SOFT_RESET);

	/* Before configuring the ARM clock, atleast we need to make sure BUS clock maintains the proper ratio with ARM clock */
	pChipcHw->ACLKClock =
	    (pChipcHw->
	     ACLKClock & ~chipcHw_REG_ACLKClock_CLK_DIV_MASK) | (initParam->
								 armBusRatio &
								 chipcHw_REG_ACLKClock_CLK_DIV_MASK);

	/* Set various core component frequencies. The order in which this is done is important for some. */
	/* The RTBUS (DDR PHY) is derived from the BUS, and the BUS from the ARM, and VPM needs to know BUS */
	/* frequency to find its ratio with the BUS.  Hence we must set the ARM first, followed by the BUS,  */
	/* then VPM and RTBUS. */

	chipcHw_setClockFrequency(chipcHw_CLOCK_ARM,
				  initParam->busClockFreqHz *
				  initParam->armBusRatio);
	chipcHw_setClockFrequency(chipcHw_CLOCK_BUS, initParam->busClockFreqHz);
	chipcHw_setClockFrequency(chipcHw_CLOCK_VPM,
				  initParam->busClockFreqHz *
				  initParam->vpmBusRatio);
	chipcHw_setClockFrequency(chipcHw_CLOCK_DDR,
				  initParam->busClockFreqHz *
				  initParam->ddrBusRatio);
	chipcHw_setClockFrequency(chipcHw_CLOCK_RTBUS,
				  initParam->busClockFreqHz / 2);
}