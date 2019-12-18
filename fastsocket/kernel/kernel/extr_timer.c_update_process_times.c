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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  account_process_tick (struct task_struct*,int) ; 
 struct task_struct* current ; 
 scalar_t__ in_irq () ; 
 int /*<<< orphan*/  irq_work_run () ; 
 int /*<<< orphan*/  printk_tick () ; 
 int /*<<< orphan*/  rcu_check_callbacks (int,int) ; 
 int /*<<< orphan*/  run_local_timers () ; 
 int /*<<< orphan*/  run_posix_cpu_timers (struct task_struct*) ; 
 int /*<<< orphan*/  scheduler_tick () ; 
 int smp_processor_id () ; 

void update_process_times(int user_tick)
{
	struct task_struct *p = current;
	int cpu = smp_processor_id();

	/* Note: this timer irq context must be accounted for as well. */
	account_process_tick(p, user_tick);
	run_local_timers();
	rcu_check_callbacks(cpu, user_tick);
	printk_tick();
#ifdef CONFIG_IRQ_WORK
	if (in_irq())
		irq_work_run();
#endif
	scheduler_tick();
	run_posix_cpu_timers(p);
}