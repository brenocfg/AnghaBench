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
struct TYPE_2__ {int VPMClock; } ;

/* Variables and functions */
 int MAX_PHASE_ADJUST_COUNT ; 
 int MAX_PHASE_ALIGN_ATTEMPTS ; 
 int /*<<< orphan*/  REG_LOCAL_IRQ_RESTORE ; 
 int /*<<< orphan*/  REG_LOCAL_IRQ_SAVE ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_COMP ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT ; 
 int chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE ; 
 TYPE_1__* pChipcHw ; 
 int /*<<< orphan*/  reg32_write (int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int vpmPhaseAlignA0(void)
{
	uint32_t phaseControl;
	uint32_t phaseValue;
	uint32_t prevPhaseComp;
	int iter = 0;
	int adjustCount = 0;
	int count = 0;

	for (iter = 0; (iter < MAX_PHASE_ALIGN_ATTEMPTS) && (adjustCount < MAX_PHASE_ADJUST_COUNT); iter++) {
		phaseControl = (pChipcHw->VPMClock & chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK) >> chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT;
		phaseValue = 0;
		prevPhaseComp = 0;

		/* Step 1: Look for falling PH_COMP transition */

		/* Read the contents of VPM Clock resgister */
		phaseValue = pChipcHw->VPMClock;
		do {
			/* Store previous value of phase comparator */
			prevPhaseComp = phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP;
			/* Change the value of PH_CTRL. */
			reg32_write(&pChipcHw->VPMClock, (pChipcHw->VPMClock & (~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK)) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT));
			/* Wait atleast 20 ns */
			udelay(1);
			/* Toggle the LOAD_CH after phase control is written. */
			pChipcHw->VPMClock ^= chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;
			/* Read the contents of  VPM Clock resgister. */
			phaseValue = pChipcHw->VPMClock;

			if ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) == 0x0) {
				phaseControl = (0x3F & (phaseControl - 1));
			} else {
				/* Increment to the Phase count value for next write, if Phase is not stable. */
				phaseControl = (0x3F & (phaseControl + 1));
			}
			/* Count number of adjustment made */
			adjustCount++;
		} while (((prevPhaseComp == (phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP)) ||	/* Look for a transition */
			  ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) != 0x0)) &&	/* Look for a falling edge */
			 (adjustCount < MAX_PHASE_ADJUST_COUNT)	/* Do not exceed the limit while trying */
		    );

		if (adjustCount >= MAX_PHASE_ADJUST_COUNT) {
			/* Failed to align VPM phase after MAX_PHASE_ADJUST_COUNT tries */
			return -1;
		}

		/* Step 2: Keep moving forward to make sure falling PH_COMP transition was valid */

		for (count = 0; (count < 5) && ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) == 0); count++) {
			phaseControl = (0x3F & (phaseControl + 1));
			reg32_write(&pChipcHw->VPMClock, (pChipcHw->VPMClock & (~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK)) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT));
			/* Wait atleast 20 ns */
			udelay(1);
			/* Toggle the LOAD_CH after phase control is written. */
			pChipcHw->VPMClock ^= chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;
			phaseValue = pChipcHw->VPMClock;
			/* Count number of adjustment made */
			adjustCount++;
		}

		if (adjustCount >= MAX_PHASE_ADJUST_COUNT) {
			/* Failed to align VPM phase after MAX_PHASE_ADJUST_COUNT tries */
			return -1;
		}

		if (count != 5) {
			/* Detected false transition */
			continue;
		}

		/* Step 3: Keep moving backward to make sure falling PH_COMP transition was stable */

		for (count = 0; (count < 3) && ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) == 0); count++) {
			phaseControl = (0x3F & (phaseControl - 1));
			reg32_write(&pChipcHw->VPMClock, (pChipcHw->VPMClock & (~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK)) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT));
			/* Wait atleast 20 ns */
			udelay(1);
			/* Toggle the LOAD_CH after phase control is written. */
			pChipcHw->VPMClock ^= chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;
			phaseValue = pChipcHw->VPMClock;
			/* Count number of adjustment made */
			adjustCount++;
		}

		if (adjustCount >= MAX_PHASE_ADJUST_COUNT) {
			/* Failed to align VPM phase after MAX_PHASE_ADJUST_COUNT tries */
			return -1;
		}

		if (count != 3) {
			/* Detected noisy transition */
			continue;
		}

		/* Step 4: Keep moving backward before the original transition took place. */

		for (count = 0; (count < 5); count++) {
			phaseControl = (0x3F & (phaseControl - 1));
			reg32_write(&pChipcHw->VPMClock, (pChipcHw->VPMClock & (~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK)) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT));
			/* Wait atleast 20 ns */
			udelay(1);
			/* Toggle the LOAD_CH after phase control is written. */
			pChipcHw->VPMClock ^= chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;
			phaseValue = pChipcHw->VPMClock;
			/* Count number of adjustment made */
			adjustCount++;
		}

		if (adjustCount >= MAX_PHASE_ADJUST_COUNT) {
			/* Failed to align VPM phase after MAX_PHASE_ADJUST_COUNT tries */
			return -1;
		}

		if ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) == 0) {
			/* Detected false transition */
			continue;
		}

		/* Step 5: Re discover the valid transition */

		do {
			/* Store previous value of phase comparator */
			prevPhaseComp = phaseValue;
			/* Change the value of PH_CTRL. */
			reg32_write(&pChipcHw->VPMClock, (pChipcHw->VPMClock & (~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK)) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT));
			/* Wait atleast 20 ns */
			udelay(1);
			/* Toggle the LOAD_CH after phase control is written. */
			pChipcHw->VPMClock ^=
			    chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;
			/* Read the contents of  VPM Clock resgister. */
			phaseValue = pChipcHw->VPMClock;

			if ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) == 0x0) {
				phaseControl = (0x3F & (phaseControl - 1));
			} else {
				/* Increment to the Phase count value for next write, if Phase is not stable. */
				phaseControl = (0x3F & (phaseControl + 1));
			}

			/* Count number of adjustment made */
			adjustCount++;
		} while (((prevPhaseComp == (phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP)) || ((phaseValue & chipcHw_REG_PLL_CLOCK_PHASE_COMP) != 0x0)) && (adjustCount < MAX_PHASE_ADJUST_COUNT));

		if (adjustCount >= MAX_PHASE_ADJUST_COUNT) {
			/* Failed to align VPM phase after MAX_PHASE_ADJUST_COUNT tries  */
			return -1;
		} else {
			/* Valid phase must have detected */
			break;
		}
	}

	/* For VPM Phase should be perfectly aligned. */
	phaseControl = (((pChipcHw->VPMClock >> chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT) - 1) & 0x3F);
	{
		REG_LOCAL_IRQ_SAVE;

		pChipcHw->VPMClock = (pChipcHw->VPMClock & ~chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_MASK) | (phaseControl << chipcHw_REG_PLL_CLOCK_PHASE_CONTROL_SHIFT);
		/* Load new phase value */
		pChipcHw->VPMClock ^= chipcHw_REG_PLL_CLOCK_PHASE_UPDATE_ENABLE;

		REG_LOCAL_IRQ_RESTORE;
	}
	/* Return the status */
	return (int)adjustCount;
}