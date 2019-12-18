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
typedef  int u32 ;

/* Variables and functions */
 int EIO ; 
 int MFGPT_CMP1 ; 
#define  MFGPT_EVENT_IRQ 130 
#define  MFGPT_EVENT_NMI 129 
#define  MFGPT_EVENT_RESET 128 
 int MFGPT_MAX_TIMERS ; 
 int MSR_MFGPT_IRQ ; 
 int MSR_MFGPT_NR ; 
 int /*<<< orphan*/  rdmsr (int,int,int) ; 
 int /*<<< orphan*/  wrmsr (int,int,int) ; 

int geode_mfgpt_toggle_event(int timer, int cmp, int event, int enable)
{
	u32 msr, mask, value, dummy;
	int shift = (cmp == MFGPT_CMP1) ? 0 : 8;

	if (timer < 0 || timer >= MFGPT_MAX_TIMERS)
		return -EIO;

	/*
	 * The register maps for these are described in sections 6.17.1.x of
	 * the AMD Geode CS5536 Companion Device Data Book.
	 */
	switch (event) {
	case MFGPT_EVENT_RESET:
		/*
		 * XXX: According to the docs, we cannot reset timers above
		 * 6; that is, resets for 7 and 8 will be ignored.  Is this
		 * a problem?   -dilinger
		 */
		msr = MSR_MFGPT_NR;
		mask = 1 << (timer + 24);
		break;

	case MFGPT_EVENT_NMI:
		msr = MSR_MFGPT_NR;
		mask = 1 << (timer + shift);
		break;

	case MFGPT_EVENT_IRQ:
		msr = MSR_MFGPT_IRQ;
		mask = 1 << (timer + shift);
		break;

	default:
		return -EIO;
	}

	rdmsr(msr, value, dummy);

	if (enable)
		value |= mask;
	else
		value &= ~mask;

	wrmsr(msr, value, dummy);
	return 0;
}