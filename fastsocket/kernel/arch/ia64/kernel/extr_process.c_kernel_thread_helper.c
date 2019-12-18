#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  old_k1; int /*<<< orphan*/  old_iob; int /*<<< orphan*/  task_size; int /*<<< orphan*/  map_base; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAP_BASE ; 
 int /*<<< orphan*/  DEFAULT_TASK_SIZE ; 
 int /*<<< orphan*/  IA64_KR_IO_BASE ; 
 int /*<<< orphan*/  IA64_KR_TSSD ; 
 scalar_t__ IS_IA32_PROCESS (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ia64_set_kr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 
 int /*<<< orphan*/  task_pt_regs (TYPE_2__*) ; 

int
kernel_thread_helper (int (*fn)(void *), void *arg)
{
#ifdef CONFIG_IA32_SUPPORT
	if (IS_IA32_PROCESS(task_pt_regs(current))) {
		/* A kernel thread is always a 64-bit process. */
		current->thread.map_base  = DEFAULT_MAP_BASE;
		current->thread.task_size = DEFAULT_TASK_SIZE;
		ia64_set_kr(IA64_KR_IO_BASE, current->thread.old_iob);
		ia64_set_kr(IA64_KR_TSSD, current->thread.old_k1);
	}
#endif
	return (*fn)(arg);
}