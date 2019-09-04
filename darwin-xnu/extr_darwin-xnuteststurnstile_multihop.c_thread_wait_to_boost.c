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
typedef  int /*<<< orphan*/  thread_info_t ;
struct TYPE_2__ {int pth_priority; } ;
typedef  TYPE_1__ thread_extended_info_data_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_OPTION_DEPRESS ; 
 int /*<<< orphan*/  THREAD_EXTENDED_INFO ; 
 int /*<<< orphan*/  THREAD_EXTENDED_INFO_COUNT ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  thread_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thread_wait_to_boost(mach_port_t thread_port, mach_port_t yield_thread, int priority)
{
	thread_extended_info_data_t extended_info;
	kern_return_t kr;

	while (1) {
		mach_msg_type_number_t count = THREAD_EXTENDED_INFO_COUNT;
		kr = thread_info(thread_port, THREAD_EXTENDED_INFO,
				   (thread_info_t)&extended_info, &count);

		T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "thread_info");

		if (extended_info.pth_priority >= priority) {
			T_LOG("Target thread boosted\n");
			break;
		}
		thread_switch(yield_thread, SWITCH_OPTION_DEPRESS, 0);
	}
}