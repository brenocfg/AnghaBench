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
typedef  int uint32_t ;
struct TYPE_2__ {int VPMClock; int /*<<< orphan*/  Spare1; } ;

/* Variables and functions */
 int MAX_PHASE_ADJUST_COUNT ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE ; 
 int /*<<< orphan*/  chipcHw_REG_SPARE1_VPM_BUS_ACCESS_ENABLE ; 
 scalar_t__ chipcHw_REV_NUMBER_A0 ; 
 scalar_t__ chipcHw_getChipRevisionNumber () ; 
 int chipcHw_getVpmHwPhaseAlignStatus () ; 
 int chipcHw_getVpmPhaseControl () ; 
 int /*<<< orphan*/  chipcHw_vpmHwPhaseAlignDisable () ; 
 int /*<<< orphan*/  chipcHw_vpmSwPhaseAlignEnable () ; 
 TYPE_1__* pChipcHw ; 
 int /*<<< orphan*/  reg32_write (int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int vpmPhaseAlignA0 () ; 

int chipcHw_vpmPhaseAlign(void)
{

	if (chipcHw_getChipRevisionNumber() == chipcHw_REV_NUMBER_A0) {
		return vpmPhaseAlignA0();
	} else {
		uint32_t phaseControl = chipcHw_getVpmPhaseControl();
		uint32_t phaseValue = 0;
		int adjustCount = 0;

		/* Disable VPM access */
		pChipcHw->Spare1 &= ~chipcHw_REG_SPARE1_VPM_BUS_ACCESS_ENABLE;
		/* Disable HW VPM phase alignment  */
		chipcHw_vpmHwPhaseAlignDisable();
		/* Enable SW VPM phase alignment  */
		chipcHw_vpmSwPhaseAlignEnable();
		/* Adjust VPM phase */
		while (adjustCount < MAX_PHASE_ADJUST_COUNT) {
			phaseValue = chipcHw_getVpmHwPhaseAlignStatus();

			/* Adjust phase control value */
			if (phaseValue > 0xF) {
				/* Increment phase control value */
				phaseControl++;
			} else if (phaseValue < 0xF) {
				/* Decrement phase control value */
				phaseControl--;
			} else {
				/* Enable VPM access */
				pChipcHw->Spare1 |= chipcHw_REG_SPARE1_VPM_BUS_ACCESS_ENABLE;
				/* Return adjust count */
				return adjustCount;
			}
			/* Change the value of PH_CTRL. */
			reg32_write(&pChipcHw->VPMClock, (pChipcHw->VPMClock & (~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK)) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT));
			/* Wait atleast 20 ns */
			udelay(1);
			/* Toggle the LOAD_CH after phase control is written. */
			pChipcHw->VPMClock ^= chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;
			/* Count adjustment */
			adjustCount++;
		}
	}

	/* Disable VPM access */
	pChipcHw->Spare1 &= ~chipcHw_REG_SPARE1_VPM_BUS_ACCESS_ENABLE;
	return -1;
}