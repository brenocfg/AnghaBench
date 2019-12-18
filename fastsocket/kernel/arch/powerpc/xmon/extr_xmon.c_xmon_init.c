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

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_ISERIES ; 
 int /*<<< orphan*/ * __debugger ; 
 int /*<<< orphan*/ * __debugger_bpt ; 
 int /*<<< orphan*/ * __debugger_dabr_match ; 
 int /*<<< orphan*/ * __debugger_fault_handler ; 
 int /*<<< orphan*/ * __debugger_iabr_match ; 
 int /*<<< orphan*/ * __debugger_ipi ; 
 int /*<<< orphan*/ * __debugger_sstep ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmon ; 
 int /*<<< orphan*/ * xmon_bpt ; 
 int /*<<< orphan*/ * xmon_dabr_match ; 
 int /*<<< orphan*/ * xmon_fault_handler ; 
 int /*<<< orphan*/ * xmon_iabr_match ; 
 int /*<<< orphan*/ * xmon_ipi ; 
 int /*<<< orphan*/  xmon_map_scc () ; 
 int /*<<< orphan*/ * xmon_sstep ; 

__attribute__((used)) static void xmon_init(int enable)
{
#ifdef CONFIG_PPC_ISERIES
	if (firmware_has_feature(FW_FEATURE_ISERIES))
		return;
#endif
	if (enable) {
		__debugger = xmon;
		__debugger_ipi = xmon_ipi;
		__debugger_bpt = xmon_bpt;
		__debugger_sstep = xmon_sstep;
		__debugger_iabr_match = xmon_iabr_match;
		__debugger_dabr_match = xmon_dabr_match;
		__debugger_fault_handler = xmon_fault_handler;
	} else {
		__debugger = NULL;
		__debugger_ipi = NULL;
		__debugger_bpt = NULL;
		__debugger_sstep = NULL;
		__debugger_iabr_match = NULL;
		__debugger_dabr_match = NULL;
		__debugger_fault_handler = NULL;
	}
	xmon_map_scc();
}