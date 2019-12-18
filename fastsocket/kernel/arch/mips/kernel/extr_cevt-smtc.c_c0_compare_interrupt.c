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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  vpe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_1__* cpu_data ; 
 int /*<<< orphan*/  handle_perf_irq (int) ; 
 int read_c0_cause () ; 
 int /*<<< orphan*/  read_c0_compare () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  smtc_distribute_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_compare (int /*<<< orphan*/ ) ; 

irqreturn_t c0_compare_interrupt(int irq, void *dev_id)
{
	int cpu = smp_processor_id();

	/* If we're running SMTC, we've got MIPS MT and therefore MIPS32R2 */
	handle_perf_irq(1);

	if (read_c0_cause() & (1 << 30)) {
		/* Clear Count/Compare Interrupt */
		write_c0_compare(read_c0_compare());
		smtc_distribute_timer(cpu_data[cpu].vpe_id);
	}
	return IRQ_HANDLED;
}