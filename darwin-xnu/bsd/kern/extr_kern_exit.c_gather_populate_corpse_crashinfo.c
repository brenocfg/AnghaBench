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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_2__ {scalar_t__ ri_phys_footprint; } ;
struct rusage_superset {TYPE_1__ ri; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_INFO_CURRENT ; 
 int /*<<< orphan*/  gather_rusage_info (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populate_corpse_crashinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rusage_superset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ; 

void gather_populate_corpse_crashinfo(proc_t p, task_t corpse_task,
		mach_exception_data_type_t code, mach_exception_data_type_t subcode,
		uint64_t *udata_buffer, int num_udata, void *reason)
{
	struct rusage_superset rup;

	gather_rusage_info(p, &rup.ri, RUSAGE_INFO_CURRENT);
	rup.ri.ri_phys_footprint = 0;
	populate_corpse_crashinfo(p, corpse_task, &rup, code, subcode,
			udata_buffer, num_udata, reason);
}