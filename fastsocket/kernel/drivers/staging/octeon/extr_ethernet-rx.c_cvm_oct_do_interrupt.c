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
struct TYPE_2__ {int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_POW_WQ_INT ; 
 scalar_t__ INTERRUPT_LIMIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_1__* cvm_oct_tasklet ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int pow_receive_group ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

irqreturn_t cvm_oct_do_interrupt(int cpl, void *dev_id)
{
	/* Acknowledge the interrupt */
	if (INTERRUPT_LIMIT)
		cvmx_write_csr(CVMX_POW_WQ_INT, 1 << pow_receive_group);
	else
		cvmx_write_csr(CVMX_POW_WQ_INT, 0x10001 << pow_receive_group);
	preempt_disable();
	tasklet_schedule(&cvm_oct_tasklet[smp_processor_id()].t);
	preempt_enable();
	return IRQ_HANDLED;
}