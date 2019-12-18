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
struct TYPE_2__ {int /*<<< orphan*/  selfipis; int /*<<< orphan*/  timerints; } ;

/* Variables and functions */
 int NR_CPUS ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* smtc_cpu_stats ; 
 int /*<<< orphan*/  smtc_fpu_recoveries ; 
 int /*<<< orphan*/  smtc_ipi_qdump () ; 

void smtc_soft_dump(void)
{
	int i;

	printk("Counter Interrupts taken per CPU (TC)\n");
	for (i=0; i < NR_CPUS; i++) {
		printk("%d: %ld\n", i, smtc_cpu_stats[i].timerints);
	}
	printk("Self-IPI invocations:\n");
	for (i=0; i < NR_CPUS; i++) {
		printk("%d: %ld\n", i, smtc_cpu_stats[i].selfipis);
	}
	smtc_ipi_qdump();
	printk("%d Recoveries of \"stolen\" FPU\n",
	       atomic_read(&smtc_fpu_recoveries));
}