#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {int task_nonvolatile_objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,int*) ; 
 int /*<<< orphan*/  assert (int) ; 

void
vm_purgeable_nonvolatile_owner_update(
	task_t	owner,
	int	delta)
{
	if (owner == NULL || delta == 0) {
		return;
	}

	if (delta > 0) {
		assert(owner->task_nonvolatile_objects >= 0);
		OSAddAtomic(delta, &owner->task_nonvolatile_objects);
		assert(owner->task_nonvolatile_objects > 0);
	} else {
		assert(owner->task_nonvolatile_objects > delta);
		OSAddAtomic(delta, &owner->task_nonvolatile_objects);
		assert(owner->task_nonvolatile_objects >= 0);
	}
}