#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpu_workqueue_struct {scalar_t__ thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ current ; 
 TYPE_1__* keventd_wq ; 
 struct cpu_workqueue_struct* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 

int current_is_keventd(void)
{
	struct cpu_workqueue_struct *cwq;
	int cpu = raw_smp_processor_id(); /* preempt-safe: keventd is per-cpu */
	int ret = 0;

	BUG_ON(!keventd_wq);

	cwq = per_cpu_ptr(keventd_wq->cpu_wq, cpu);
	if (current == cwq->thread)
		ret = 1;

	return ret;

}