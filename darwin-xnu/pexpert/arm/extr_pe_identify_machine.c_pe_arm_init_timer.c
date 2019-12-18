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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  struct tbd_ops* tbd_ops_t ;
struct tbd_ops {int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_2__ {scalar_t__* timebase_frequency_hz; } ;
typedef  scalar_t__ ARM_BOARD_WFE_TIMEOUT_NS ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  PMGR_EVENT_TMR_CTL_EN ; 
 int PMGR_INTERVAL_TMR_CTL_CLR_INT ; 
 int PMGR_INTERVAL_TMR_CTL_EN ; 
 int /*<<< orphan*/  aic_write32 (int /*<<< orphan*/ ,int) ; 
 struct tbd_ops bcm2837_funcs ; 
 int /*<<< orphan*/  fleh_fiq_generic ; 
 TYPE_1__ gPEClockFrequencyInfo ; 
 int /*<<< orphan*/  gPESoCDeviceType ; 
 int /*<<< orphan*/  gPicBase ; 
 int /*<<< orphan*/  gSocPhys ; 
 int /*<<< orphan*/  gTimerBase ; 
 int /*<<< orphan*/  kAICTmrCfg ; 
 int kAICTmrCfgEn ; 
 int /*<<< orphan*/  kAICTmrCnt ; 
 int /*<<< orphan*/  kAICTmrIntStat ; 
 int kAICTmrIntStatPct ; 
 int /*<<< orphan*/  ml_init_timebase (void*,struct tbd_ops*,int /*<<< orphan*/ ,int) ; 
 int rPMGR_EVENT_TMR ; 
 int /*<<< orphan*/  rPMGR_EVENT_TMR_CTL ; 
 int rPMGR_EVENT_TMR_PERIOD ; 
 int rPMGR_INTERVAL_TMR ; 
 int rPMGR_INTERVAL_TMR_CTL ; 
 struct tbd_ops s5l8960x_funcs ; 
 struct tbd_ops s7002_funcs ; 
 struct tbd_ops s8000_funcs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct tbd_ops t7000_funcs ; 
 struct tbd_ops t8002_funcs ; 
 struct tbd_ops t8010_funcs ; 
 struct tbd_ops t8011_funcs ; 
 struct tbd_ops t8015_funcs ; 

__attribute__((used)) static uint32_t 
pe_arm_init_timer(void *args)
{
	vm_offset_t	pic_base = 0;
	vm_offset_t	timer_base = 0;
	vm_offset_t	soc_phys;
	vm_offset_t 	eoi_addr = 0;
	uint32_t 	eoi_value = 0;
	struct tbd_ops  generic_funcs = {&fleh_fiq_generic, NULL, NULL};
	tbd_ops_t	tbd_funcs = &generic_funcs;

	/* The SoC headers expect to use pic_base, timer_base, etc... */
	pic_base = gPicBase;
	timer_base = gTimerBase;
	soc_phys = gSocPhys;

#if defined(ARM_BOARD_CLASS_S5L8960X)
	if (!strcmp(gPESoCDeviceType, "s5l8960x-io")) {

		tbd_funcs = &s5l8960x_funcs;
	} else
#endif 
#if defined(ARM_BOARD_CLASS_T7000)
	if (!strcmp(gPESoCDeviceType, "t7000-io") ||
            !strcmp(gPESoCDeviceType, "t7001-io")) {
		tbd_funcs = &t7000_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_S7002)
	if (!strcmp(gPESoCDeviceType, "s7002-io")) {

#ifdef ARM_BOARD_WFE_TIMEOUT_NS
		// Enable the WFE Timer
		rPMGR_EVENT_TMR_PERIOD = ((uint64_t)(ARM_BOARD_WFE_TIMEOUT_NS) * gPEClockFrequencyInfo.timebase_frequency_hz) / NSEC_PER_SEC;
		rPMGR_EVENT_TMR = rPMGR_EVENT_TMR_PERIOD;
		rPMGR_EVENT_TMR_CTL = PMGR_EVENT_TMR_CTL_EN;
#endif /* ARM_BOARD_WFE_TIMEOUT_NS */

		rPMGR_INTERVAL_TMR = 0x7FFFFFFF;
		rPMGR_INTERVAL_TMR_CTL = PMGR_INTERVAL_TMR_CTL_EN | PMGR_INTERVAL_TMR_CTL_CLR_INT;

		eoi_addr = timer_base;
		eoi_value = PMGR_INTERVAL_TMR_CTL_EN | PMGR_INTERVAL_TMR_CTL_CLR_INT;
		tbd_funcs = &s7002_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_S8000)
	if (!strcmp(gPESoCDeviceType, "s8000-io") ||
	    !strcmp(gPESoCDeviceType, "s8001-io")) {
		tbd_funcs = &s8000_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_T8002)
	if (!strcmp(gPESoCDeviceType, "t8002-io") ||
	    !strcmp(gPESoCDeviceType, "t8004-io")) {

		/* Enable the Decrementer */
		aic_write32(kAICTmrCnt, 0x7FFFFFFF);
		aic_write32(kAICTmrCfg, kAICTmrCfgEn);
		aic_write32(kAICTmrIntStat, kAICTmrIntStatPct);
#ifdef ARM_BOARD_WFE_TIMEOUT_NS
		// Enable the WFE Timer
		rPMGR_EVENT_TMR_PERIOD = ((uint64_t)(ARM_BOARD_WFE_TIMEOUT_NS) * gPEClockFrequencyInfo.timebase_frequency_hz) / NSEC_PER_SEC;
		rPMGR_EVENT_TMR = rPMGR_EVENT_TMR_PERIOD;
		rPMGR_EVENT_TMR_CTL = PMGR_EVENT_TMR_CTL_EN;
#endif /* ARM_BOARD_WFE_TIMEOUT_NS */

		eoi_addr = pic_base;
		eoi_value = kAICTmrIntStatPct;
		tbd_funcs = &t8002_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_T8010)
	if (!strcmp(gPESoCDeviceType, "t8010-io")) {
		tbd_funcs = &t8010_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_T8011)
	if (!strcmp(gPESoCDeviceType, "t8011-io")) {
		tbd_funcs = &t8011_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_T8015)
	if (!strcmp(gPESoCDeviceType, "t8015-io")) {
		tbd_funcs = &t8015_funcs;
	} else
#endif
#if defined(ARM_BOARD_CLASS_BCM2837)
	if (!strcmp(gPESoCDeviceType, "bcm2837-io")) {
		tbd_funcs = &bcm2837_funcs;
	} else
#endif
		return 0;

	if (args != NULL)
		ml_init_timebase(args, tbd_funcs, eoi_addr, eoi_value);

	return 1;
}