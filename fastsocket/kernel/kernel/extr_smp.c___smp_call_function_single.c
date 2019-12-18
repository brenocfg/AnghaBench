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
struct call_single_data {int /*<<< orphan*/  info; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csd_lock (struct call_single_data*) ; 
 int /*<<< orphan*/  generic_exec_single (int,struct call_single_data*,int) ; 
 unsigned int get_cpu () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  oops_in_progress ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void __smp_call_function_single(int cpu, struct call_single_data *data,
				int wait)
{
	unsigned int this_cpu;
	unsigned long flags;

	this_cpu = get_cpu();
	/*
	 * Can deadlock when called with interrupts disabled.
	 * We allow cpu's that are not yet online though, as no one else can
	 * send smp call function interrupt to this cpu and as such deadlocks
	 * can't happen.
	 */
	WARN_ON_ONCE(cpu_online(smp_processor_id()) && wait && irqs_disabled()
		     && !oops_in_progress);

	if (cpu == this_cpu) {
		local_irq_save(flags);
		data->func(data->info);
		local_irq_restore(flags);
	} else {
		csd_lock(data);
		generic_exec_single(cpu, data, wait);
	}
	put_cpu();
}