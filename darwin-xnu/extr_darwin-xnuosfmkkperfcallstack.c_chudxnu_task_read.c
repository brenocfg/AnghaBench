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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ current_task () ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  get_task_map (scalar_t__) ; 
 scalar_t__ ml_at_interrupt_context () ; 
 int /*<<< orphan*/  vm_map_read_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
chudxnu_task_read(
		task_t      task,
		void        *kernaddr,
		uint64_t    usraddr,
		vm_size_t   size)
{
	//ppc version ported to arm
	kern_return_t ret = KERN_SUCCESS;

	if (ml_at_interrupt_context()) {
		return KERN_FAILURE;    // can't look at tasks on interrupt stack
	}

	if (current_task() == task) {
		thread_t      cur_thr = current_thread();
		vm_offset_t   recover_handler = cur_thr->recover; 

		if (copyin(usraddr, kernaddr, size)) {
			ret = KERN_FAILURE;
		}
		cur_thr->recover = recover_handler;
	} else {
		vm_map_t map = get_task_map(task);
		ret = vm_map_read_user(map, usraddr, kernaddr, size);
	}

	return ret;
}