#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  host_t ;
typedef  int /*<<< orphan*/  host_info_t ;
struct TYPE_3__ {int max_cpus; } ;
typedef  TYPE_1__ host_basic_info_data_t ;
struct TYPE_4__ {int /*<<< orphan*/  vm_restricted_to_single_processor; } ;

/* Variables and functions */
 scalar_t__ BSD_HOST ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HOST_BASIC_INFO ; 
 int /*<<< orphan*/  HOST_BASIC_INFO_COUNT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  host_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ vm_pageout_state ; 

void
vm_set_restrictions()
{
	host_basic_info_data_t hinfo;
	mach_msg_type_number_t count = HOST_BASIC_INFO_COUNT;

#define BSD_HOST 1
	host_info((host_t)BSD_HOST, HOST_BASIC_INFO, (host_info_t)&hinfo, &count);

	assert(hinfo.max_cpus > 0);

	if (hinfo.max_cpus <= 3) {
		/*
		 * on systems with a limited number of CPUS, bind the
		 * 4 major threads that can free memory and that tend to use
		 * a fair bit of CPU under pressured conditions to a single processor.
		 * This insures that these threads don't hog all of the available CPUs
		 * (important for camera launch), while allowing them to run independently
		 * w/r to locks... the 4 threads are
		 * vm_pageout_scan,  vm_pageout_iothread_internal (compressor),
		 * vm_compressor_swap_trigger_thread (minor and major compactions),
		 * memorystatus_thread (jetsams).
		 *
		 * the first time the thread is run, it is responsible for checking the
		 * state of vm_restricted_to_single_processor, and if TRUE it calls
		 * thread_bind_master...  someday this should be replaced with a group
		 * scheduling mechanism and KPI.
		 */
		vm_pageout_state.vm_restricted_to_single_processor = TRUE;
	} else
		vm_pageout_state.vm_restricted_to_single_processor = FALSE;
}