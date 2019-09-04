#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_5__ {int /*<<< orphan*/  map; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_NULL ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_reference_swap (int /*<<< orphan*/ ) ; 

vm_map_t  get_task_map_reference(task_t t)
{
	vm_map_t m;

	if (t == NULL)
		return VM_MAP_NULL;

	task_lock(t);
	if (!t->active) {
		task_unlock(t);
		return VM_MAP_NULL;
	}
	m = t->map;
	vm_map_reference_swap(m);
	task_unlock(t);
	return m;
}