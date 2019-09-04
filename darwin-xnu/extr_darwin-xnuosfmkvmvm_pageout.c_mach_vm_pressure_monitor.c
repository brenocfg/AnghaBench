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
typedef  scalar_t__ wait_result_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ freed_external; scalar_t__ freed_internal; scalar_t__ freed_cleaned; scalar_t__ freed_speculative; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ABORTED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ THREAD_AWAKENED ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 scalar_t__ THREAD_INTERRUPTED ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 scalar_t__ THREAD_WAITING ; 
 unsigned int VM_PAGEOUT_STAT_BEFORE (unsigned int) ; 
 scalar_t__ assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int mach_vm_ctl_page_free_wanted () ; 
 scalar_t__ thread_block (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_free_count ; 
 scalar_t__ vm_page_free_target ; 
 int /*<<< orphan*/  vm_page_free_wanted ; 
 unsigned int vm_pageout_stat_now ; 
 TYPE_1__* vm_pageout_stats ; 

kern_return_t
mach_vm_pressure_monitor(
	boolean_t	wait_for_pressure,
	unsigned int	nsecs_monitored,
	unsigned int	*pages_reclaimed_p,
	unsigned int	*pages_wanted_p)
{
	wait_result_t	wr;
	unsigned int	vm_pageout_then, vm_pageout_now;
	unsigned int	pages_reclaimed;
	unsigned int    units_of_monitor;

	units_of_monitor = 8 * nsecs_monitored;
	/*
	 * We don't take the vm_page_queue_lock here because we don't want
	 * vm_pressure_monitor() to get in the way of the vm_pageout_scan()
	 * thread when it's trying to reclaim memory.  We don't need fully
	 * accurate monitoring anyway...
	 */

	if (wait_for_pressure) {
		/* wait until there's memory pressure */
		while (vm_page_free_count >= vm_page_free_target) {
			wr = assert_wait((event_t) &vm_page_free_wanted,
					 THREAD_INTERRUPTIBLE);
			if (wr == THREAD_WAITING) {
				wr = thread_block(THREAD_CONTINUE_NULL);
			}
			if (wr == THREAD_INTERRUPTED) {
				return KERN_ABORTED;
			}
			if (wr == THREAD_AWAKENED) {
				/*
				 * The memory pressure might have already
				 * been relieved but let's not block again
				 * and let's report that there was memory
				 * pressure at some point.
				 */
				break;
			}
		}
	}

	/* provide the number of pages the system wants to reclaim */
	if (pages_wanted_p != NULL) {
		*pages_wanted_p = mach_vm_ctl_page_free_wanted();
	}

	if (pages_reclaimed_p == NULL) {
		return KERN_SUCCESS;
	}

	/* provide number of pages reclaimed in the last "nsecs_monitored" */
	vm_pageout_now = vm_pageout_stat_now;
	pages_reclaimed = 0;
	for (vm_pageout_then =
		     VM_PAGEOUT_STAT_BEFORE(vm_pageout_now);
	     vm_pageout_then != vm_pageout_now &&
		     units_of_monitor-- != 0;
	     vm_pageout_then =
		     VM_PAGEOUT_STAT_BEFORE(vm_pageout_then)) {
		pages_reclaimed += vm_pageout_stats[vm_pageout_then].freed_speculative;
		pages_reclaimed += vm_pageout_stats[vm_pageout_then].freed_cleaned;
		pages_reclaimed += vm_pageout_stats[vm_pageout_then].freed_internal;
		pages_reclaimed += vm_pageout_stats[vm_pageout_then].freed_external;
	}
	*pages_reclaimed_p = pages_reclaimed;

	return KERN_SUCCESS;
}