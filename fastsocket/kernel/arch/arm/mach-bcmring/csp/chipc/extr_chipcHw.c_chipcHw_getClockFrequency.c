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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int chipcHw_freq ;
typedef  int chipcHw_CLOCK_e ;
struct TYPE_2__ {int PLLPreDivider; int PLLPreDivider2; int DDRClock; int ARMClock; int ESWClock; int VPMClock; int ESW125Clock; int UARTClock; int SDIO0Clock; int SDIO1Clock; int SPIClock; int ETMClock; int USBClock; int LCDClock; int APMClock; int ACLKClock; int OTPClock; int I2CClock; int I2S0Clock; int RTBUSClock; int APM100Clock; int TSCClock; int LEDClock; int I2S1Clock; int PLLDivider; } ;

/* Variables and functions */
#define  NON_PLL_CLOCK 151 
#define  PLL_CLOCK 150 
#define  chipcHw_CLOCK_APM 149 
#define  chipcHw_CLOCK_APM100 148 
#define  chipcHw_CLOCK_ARM 147 
#define  chipcHw_CLOCK_BUS 146 
#define  chipcHw_CLOCK_DDR 145 
#define  chipcHw_CLOCK_ESW 144 
#define  chipcHw_CLOCK_ESW125 143 
#define  chipcHw_CLOCK_ETM 142 
#define  chipcHw_CLOCK_I2C 141 
#define  chipcHw_CLOCK_I2S0 140 
#define  chipcHw_CLOCK_I2S1 139 
#define  chipcHw_CLOCK_LCD 138 
#define  chipcHw_CLOCK_LED 137 
#define  chipcHw_CLOCK_OTP 136 
#define  chipcHw_CLOCK_RTBUS 135 
#define  chipcHw_CLOCK_SDIO0 134 
#define  chipcHw_CLOCK_SDIO1 133 
#define  chipcHw_CLOCK_SPI 132 
#define  chipcHw_CLOCK_TSC 131 
#define  chipcHw_CLOCK_UART 130 
#define  chipcHw_CLOCK_USB 129 
#define  chipcHw_CLOCK_VPM 128 
 int volatile chipcHw_REG_DIV_CLOCK_BYPASS_SELECT ; 
 int volatile chipcHw_REG_DIV_CLOCK_DIV_MASK ; 
 int volatile chipcHw_REG_PLL_CLOCK_BYPASS_SELECT ; 
 int volatile chipcHw_REG_PLL_CLOCK_MDIV_MASK ; 
 scalar_t__ chipcHw_REG_PLL_DIVIDER_FRAC ; 
 scalar_t__ chipcHw_REG_PLL_DIVIDER_NDIV_f_SS ; 
 int chipcHw_REG_PLL_PREDIVIDER_NDIV_MASK ; 
 int chipcHw_REG_PLL_PREDIVIDER_NDIV_MODE_INTEGER ; 
 int chipcHw_REG_PLL_PREDIVIDER_NDIV_MODE_MASK ; 
 int chipcHw_REG_PLL_PREDIVIDER_NDIV_SHIFT ; 
 int chipcHw_REG_PLL_PREDIVIDER_P1 ; 
 int chipcHw_REG_PLL_PREDIVIDER_P2 ; 
 scalar_t__ chipcHw_REV_NUMBER_A0 ; 
 int chipcHw_XTAL_FREQ_Hz ; 
 int chipcHw_divide (int,int volatile) ; 
 scalar_t__ chipcHw_getChipRevisionNumber () ; 
 TYPE_1__* pChipcHw ; 

chipcHw_freq chipcHw_getClockFrequency(chipcHw_CLOCK_e clock	/*  [ IN ] Configurable clock */
    ) {
	volatile uint32_t *pPLLReg = (uint32_t *) 0x0;
	volatile uint32_t *pClockCtrl = (uint32_t *) 0x0;
	volatile uint32_t *pDependentClock = (uint32_t *) 0x0;
	uint32_t vcoFreqPll1Hz = 0;	/* Effective VCO frequency for PLL1 in Hz */
	uint32_t vcoFreqPll2Hz = 0;	/* Effective VCO frequency for PLL2 in Hz */
	uint32_t dependentClockType = 0;
	uint32_t vcoHz = 0;

	/* Get VCO frequencies */
	if ((pChipcHw->PLLPreDivider & chipcHw_REG_PLL_PREDIVIDER_NDIV_MODE_MASK) != chipcHw_REG_PLL_PREDIVIDER_NDIV_MODE_INTEGER) {
		uint64_t adjustFreq = 0;

		vcoFreqPll1Hz = chipcHw_XTAL_FREQ_Hz *
		    chipcHw_divide(chipcHw_REG_PLL_PREDIVIDER_P1, chipcHw_REG_PLL_PREDIVIDER_P2) *
		    ((pChipcHw->PLLPreDivider & chipcHw_REG_PLL_PREDIVIDER_NDIV_MASK) >>
		     chipcHw_REG_PLL_PREDIVIDER_NDIV_SHIFT);

		/* Adjusted frequency due to chipcHw_REG_PLL_DIVIDER_NDIV_f_SS */
		adjustFreq = (uint64_t) chipcHw_XTAL_FREQ_Hz *
			(uint64_t) chipcHw_REG_PLL_DIVIDER_NDIV_f_SS *
			chipcHw_divide(chipcHw_REG_PLL_PREDIVIDER_P1, (chipcHw_REG_PLL_PREDIVIDER_P2 * (uint64_t) chipcHw_REG_PLL_DIVIDER_FRAC));
		vcoFreqPll1Hz += (uint32_t) adjustFreq;
	} else {
		vcoFreqPll1Hz = chipcHw_XTAL_FREQ_Hz *
		    chipcHw_divide(chipcHw_REG_PLL_PREDIVIDER_P1, chipcHw_REG_PLL_PREDIVIDER_P2) *
		    ((pChipcHw->PLLPreDivider & chipcHw_REG_PLL_PREDIVIDER_NDIV_MASK) >>
		     chipcHw_REG_PLL_PREDIVIDER_NDIV_SHIFT);
	}
	vcoFreqPll2Hz =
	    chipcHw_XTAL_FREQ_Hz *
		 chipcHw_divide(chipcHw_REG_PLL_PREDIVIDER_P1, chipcHw_REG_PLL_PREDIVIDER_P2) *
	    ((pChipcHw->PLLPreDivider2 & chipcHw_REG_PLL_PREDIVIDER_NDIV_MASK) >>
	     chipcHw_REG_PLL_PREDIVIDER_NDIV_SHIFT);

	switch (clock) {
	case chipcHw_CLOCK_DDR:
		pPLLReg = &pChipcHw->DDRClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_ARM:
		pPLLReg = &pChipcHw->ARMClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_ESW:
		pPLLReg = &pChipcHw->ESWClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_VPM:
		pPLLReg = &pChipcHw->VPMClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_ESW125:
		pPLLReg = &pChipcHw->ESW125Clock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_UART:
		pPLLReg = &pChipcHw->UARTClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_SDIO0:
		pPLLReg = &pChipcHw->SDIO0Clock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_SDIO1:
		pPLLReg = &pChipcHw->SDIO1Clock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_SPI:
		pPLLReg = &pChipcHw->SPIClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_ETM:
		pPLLReg = &pChipcHw->ETMClock;
		vcoHz = vcoFreqPll1Hz;
		break;
	case chipcHw_CLOCK_USB:
		pPLLReg = &pChipcHw->USBClock;
		vcoHz = vcoFreqPll2Hz;
		break;
	case chipcHw_CLOCK_LCD:
		pPLLReg = &pChipcHw->LCDClock;
		vcoHz = vcoFreqPll2Hz;
		break;
	case chipcHw_CLOCK_APM:
		pPLLReg = &pChipcHw->APMClock;
		vcoHz = vcoFreqPll2Hz;
		break;
	case chipcHw_CLOCK_BUS:
		pClockCtrl = &pChipcHw->ACLKClock;
		pDependentClock = &pChipcHw->ARMClock;
		vcoHz = vcoFreqPll1Hz;
		dependentClockType = PLL_CLOCK;
		break;
	case chipcHw_CLOCK_OTP:
		pClockCtrl = &pChipcHw->OTPClock;
		break;
	case chipcHw_CLOCK_I2C:
		pClockCtrl = &pChipcHw->I2CClock;
		break;
	case chipcHw_CLOCK_I2S0:
		pClockCtrl = &pChipcHw->I2S0Clock;
		break;
	case chipcHw_CLOCK_RTBUS:
		pClockCtrl = &pChipcHw->RTBUSClock;
		pDependentClock = &pChipcHw->ACLKClock;
		dependentClockType = NON_PLL_CLOCK;
		break;
	case chipcHw_CLOCK_APM100:
		pClockCtrl = &pChipcHw->APM100Clock;
		pDependentClock = &pChipcHw->APMClock;
		vcoHz = vcoFreqPll2Hz;
		dependentClockType = PLL_CLOCK;
		break;
	case chipcHw_CLOCK_TSC:
		pClockCtrl = &pChipcHw->TSCClock;
		break;
	case chipcHw_CLOCK_LED:
		pClockCtrl = &pChipcHw->LEDClock;
		break;
	case chipcHw_CLOCK_I2S1:
		pClockCtrl = &pChipcHw->I2S1Clock;
		break;
	}

	if (pPLLReg) {
		/* Obtain PLL clock frequency */
		if (*pPLLReg & chipcHw_REG_PLL_CLOCK_BYPASS_SELECT) {
			/* Return crystal clock frequency when bypassed */
			return chipcHw_XTAL_FREQ_Hz;
		} else if (clock == chipcHw_CLOCK_DDR) {
			/* DDR frequency is configured in PLLDivider register */
			return chipcHw_divide (vcoHz, (((pChipcHw->PLLDivider & 0xFF000000) >> 24) ? ((pChipcHw->PLLDivider & 0xFF000000) >> 24) : 256));
		} else {
			/* From chip revision number B0, LCD clock is internally divided by 2 */
			if ((pPLLReg == &pChipcHw->LCDClock) && (chipcHw_getChipRevisionNumber() != chipcHw_REV_NUMBER_A0)) {
				vcoHz >>= 1;
			}
			/* Obtain PLL clock frequency using VCO dividers */
			return chipcHw_divide(vcoHz, ((*pPLLReg & chipcHw_REG_PLL_CLOCK_MDIV_MASK) ? (*pPLLReg & chipcHw_REG_PLL_CLOCK_MDIV_MASK) : 256));
		}
	} else if (pClockCtrl) {
		/* Obtain divider clock frequency */
		uint32_t div;
		uint32_t freq = 0;

		if (*pClockCtrl & chipcHw_REG_DIV_CLOCK_BYPASS_SELECT) {
			/* Return crystal clock frequency when bypassed */
			return chipcHw_XTAL_FREQ_Hz;
		} else if (pDependentClock) {
			/* Identify the dependent clock frequency */
			switch (dependentClockType) {
			case PLL_CLOCK:
				if (*pDependentClock & chipcHw_REG_PLL_CLOCK_BYPASS_SELECT) {
					/* Use crystal clock frequency when dependent PLL clock is bypassed */
					freq = chipcHw_XTAL_FREQ_Hz;
				} else {
					/* Obtain PLL clock frequency using VCO dividers */
					div = *pDependentClock & chipcHw_REG_PLL_CLOCK_MDIV_MASK;
					freq = div ? chipcHw_divide(vcoHz, div) : 0;
				}
				break;
			case NON_PLL_CLOCK:
				if (pDependentClock == (uint32_t *) &pChipcHw->ACLKClock) {
					freq = chipcHw_getClockFrequency (chipcHw_CLOCK_BUS);
				} else {
					if (*pDependentClock & chipcHw_REG_DIV_CLOCK_BYPASS_SELECT) {
						/* Use crystal clock frequency when dependent divider clock is bypassed */
						freq = chipcHw_XTAL_FREQ_Hz;
					} else {
						/* Obtain divider clock frequency using XTAL dividers */
						div = *pDependentClock & chipcHw_REG_DIV_CLOCK_DIV_MASK;
						freq = chipcHw_divide (chipcHw_XTAL_FREQ_Hz, (div ? div : 256));
					}
				}
				break;
			}
		} else {
			/* Dependent on crystal clock */
			freq = chipcHw_XTAL_FREQ_Hz;
		}

		div = *pClockCtrl & chipcHw_REG_DIV_CLOCK_DIV_MASK;
		return chipcHw_divide(freq, (div ? div : 256));
	}
	return 0;
}