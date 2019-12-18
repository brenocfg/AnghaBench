#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_SWITCH_USER (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int cpu_number () ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 

vm_map_t
vm_map_switch(
	vm_map_t	map)
{
	int		mycpu;
	thread_t	thread = current_thread();
	vm_map_t	oldmap = thread->map;

	mp_disable_preemption();
	mycpu = cpu_number();

	/*
	 *	Deactivate the current map and activate the requested map
	 */
	PMAP_SWITCH_USER(thread, map, mycpu);

	mp_enable_preemption();
	return(oldmap);
}