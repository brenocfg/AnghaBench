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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEMORYSTATUS_VM_MAP_FORK_ALLOWED ; 
 int /*<<< orphan*/  MEMORYSTATUS_VM_MAP_FORK_NOT_ALLOWED ; 
 int TRUE ; 
 int get_task_phys_footprint (int /*<<< orphan*/ ) ; 
 scalar_t__ max_task_footprint_mb ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  set_vm_map_fork_pidwatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
memorystatus_allowed_vm_map_fork(task_t task)
{
	boolean_t is_allowed = TRUE;   /* default */

#if CONFIG_EMBEDDED

	uint64_t footprint_in_bytes;
	uint64_t max_allowed_bytes;

	if (max_task_footprint_mb == 0) {
		set_vm_map_fork_pidwatch(task, MEMORYSTATUS_VM_MAP_FORK_ALLOWED);
		return (is_allowed);
	}

	footprint_in_bytes = get_task_phys_footprint(task);

	/*
	 * Maximum is 1/4 of the system-wide task limit.
	 */
	max_allowed_bytes = ((uint64_t)max_task_footprint_mb * 1024 * 1024) >> 2;

	if (footprint_in_bytes > max_allowed_bytes) {
		printf("memorystatus disallowed vm_map_fork %lld  %lld\n", footprint_in_bytes, max_allowed_bytes);
		set_vm_map_fork_pidwatch(task, MEMORYSTATUS_VM_MAP_FORK_NOT_ALLOWED);
		return (!is_allowed);
	}
#endif /* CONFIG_EMBEDDED */

	set_vm_map_fork_pidwatch(task, MEMORYSTATUS_VM_MAP_FORK_ALLOWED);
	return (is_allowed);

}