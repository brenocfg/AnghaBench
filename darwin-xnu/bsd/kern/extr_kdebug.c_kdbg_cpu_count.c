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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  host_t ;
typedef  int /*<<< orphan*/  host_info_t ;
struct TYPE_2__ {scalar_t__ logical_cpu_max; } ;
typedef  TYPE_1__ host_basic_info_data_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_BASIC_INFO ; 
 int /*<<< orphan*/  HOST_BASIC_INFO_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  host_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ max_ncpus ; 
 scalar_t__ ml_get_cpu_count () ; 

__attribute__((used)) static uint32_t
kdbg_cpu_count(boolean_t early_trace)
{
	if (early_trace) {
#if CONFIG_EMBEDDED
		return ml_get_cpu_count();
#else
		return max_ncpus;
#endif
	}

	host_basic_info_data_t hinfo;
	mach_msg_type_number_t count = HOST_BASIC_INFO_COUNT;
	host_info((host_t)1 /* BSD_HOST */, HOST_BASIC_INFO, (host_info_t)&hinfo, &count);
	assert(hinfo.logical_cpu_max > 0);
	return hinfo.logical_cpu_max;
}