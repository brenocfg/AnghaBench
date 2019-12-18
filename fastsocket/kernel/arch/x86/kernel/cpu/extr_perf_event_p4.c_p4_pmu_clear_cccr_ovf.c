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
typedef  int u64 ;
struct hw_perf_event {int /*<<< orphan*/  event_base; int /*<<< orphan*/  config_base; } ;

/* Variables and functions */
 int ARCH_P4_UNFLAGGED_BIT ; 
 int P4_CCCR_OVF ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int p4_pmu_clear_cccr_ovf(struct hw_perf_event *hwc)
{
	u64 v;

	/* an official way for overflow indication */
	rdmsrl(hwc->config_base, v);
	if (v & P4_CCCR_OVF) {
		wrmsrl(hwc->config_base, v & ~P4_CCCR_OVF);
		return 1;
	}

	/*
	 * In some circumstances the overflow might issue an NMI but did
	 * not set P4_CCCR_OVF bit. Because a counter holds a negative value
	 * we simply check for high bit being set, if it's cleared it means
	 * the counter has reached zero value and continued counting before
	 * real NMI signal was received:
	 */
	rdmsrl(hwc->event_base, v);
	if (!(v & ARCH_P4_UNFLAGGED_BIT))
		return 1;

	return 0;
}