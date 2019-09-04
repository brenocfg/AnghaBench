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
typedef  TYPE_1__* atm_task_descriptor_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_TASK_DEAD ; 
 int /*<<< orphan*/  atm_task_descriptor_dealloc (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
atm_task_descriptor_destroy(atm_task_descriptor_t task_descriptor)
{
	/* Mark the task dead in the task descriptor to make task descriptor eligible for cleanup. */
	lck_mtx_lock(&task_descriptor->lock);
	task_descriptor->flags = ATM_TASK_DEAD;
	lck_mtx_unlock(&task_descriptor->lock);

	atm_task_descriptor_dealloc(task_descriptor);
}