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
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_self ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WORK_VECTOR ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  apic_wait_icr_idle () ; 
 int /*<<< orphan*/  cpu_has_apic ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void arch_irq_work_raise(void)
{
#ifdef CONFIG_X86_LOCAL_APIC
	if (!cpu_has_apic)
		return;

	apic->send_IPI_self(IRQ_WORK_VECTOR);
	apic_wait_icr_idle();
#endif
}