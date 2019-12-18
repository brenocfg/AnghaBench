#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; scalar_t__ pfm_context; } ;
struct TYPE_9__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int IA64_THREAD_DBG_VALID ; 
 scalar_t__ IS_IA32_PROCESS (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ia32_drop_ia64_partial_page_list (TYPE_2__*) ; 
 int /*<<< orphan*/  ia64_drop_fpu (TYPE_2__*) ; 
 int /*<<< orphan*/  pfm_exit_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  pfm_release_debug_registers (TYPE_2__*) ; 
 int /*<<< orphan*/  task_pt_regs (TYPE_2__*) ; 

void
exit_thread (void)
{

	ia64_drop_fpu(current);
#ifdef CONFIG_PERFMON
       /* if needed, stop monitoring and flush state to perfmon context */
	if (current->thread.pfm_context)
		pfm_exit_thread(current);

	/* free debug register resources */
	if (current->thread.flags & IA64_THREAD_DBG_VALID)
		pfm_release_debug_registers(current);
#endif
	if (IS_IA32_PROCESS(task_pt_regs(current)))
		ia32_drop_ia64_partial_page_list(current);
}