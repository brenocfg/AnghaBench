#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* task_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {TYPE_1__* map; } ;
struct TYPE_13__ {TYPE_1__* map; TYPE_3__* task; } ;
struct TYPE_12__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_commit_pagezero_status (TYPE_1__*) ; 

vm_map_t
swap_task_map(task_t task, thread_t thread, vm_map_t map)
{
	vm_map_t old_map;
	boolean_t doswitch = (thread == current_thread()) ? TRUE : FALSE;

	if (task != thread->task)
		panic("swap_task_map");

	task_lock(task);
	mp_disable_preemption();

	old_map = task->map;
	thread->map = task->map = map;
	vm_commit_pagezero_status(map);

	if (doswitch) {
#if	defined(__arm__) || defined(__arm64__)
		PMAP_SWITCH_USER(thread, map, cpu_number())
#else
		pmap_switch(map->pmap);
#endif
	}
	mp_enable_preemption();
	task_unlock(task);

#if (defined(__i386__) || defined(__x86_64__)) && NCOPY_WINDOWS > 0
	inval_copy_windows(thread);
#endif

	return old_map;
}