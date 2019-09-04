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
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/ * task_array_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pet_lock ; 
 int /*<<< orphan*/ * pet_tasks ; 
 int pet_tasks_size ; 
 int tasks_count ; 
 int /*<<< orphan*/  tasks_threads_lock ; 

__attribute__((used)) static kern_return_t
pet_tasks_prepare_internal(void)
{
	lck_mtx_assert(pet_lock, LCK_MTX_ASSERT_OWNED);

	vm_size_t tasks_size_needed = 0;

	for (;;) {
		lck_mtx_lock(&tasks_threads_lock);

		/* do we have the memory we need? */
		tasks_size_needed = tasks_count * sizeof(task_t);
		if (tasks_size_needed <= pet_tasks_size) {
			break;
		}

		/* unlock and allocate more memory */
		lck_mtx_unlock(&tasks_threads_lock);

		/* grow task array */
		if (tasks_size_needed > pet_tasks_size) {
			if (pet_tasks_size != 0) {
				kfree(pet_tasks, pet_tasks_size);
			}

			assert(tasks_size_needed > 0);
			pet_tasks_size = tasks_size_needed;

			pet_tasks = (task_array_t)kalloc(pet_tasks_size);
			if (pet_tasks == NULL) {
				pet_tasks_size = 0;
				return KERN_RESOURCE_SHORTAGE;
			}
		}
	}

	return KERN_SUCCESS;
}