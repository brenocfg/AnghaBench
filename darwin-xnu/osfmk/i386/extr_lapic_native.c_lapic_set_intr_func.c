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
typedef  int /*<<< orphan*/  i386_intr_func_t ;

/* Variables and functions */
#define  LAPIC_CMCI_INTERRUPT 134 
#define  LAPIC_INTERPROCESSOR_INTERRUPT 133 
#define  LAPIC_NMI_INTERRUPT 132 
#define  LAPIC_PERFCNT_INTERRUPT 131 
#define  LAPIC_PM_INTERRUPT 130 
#define  LAPIC_THERMAL_INTERRUPT 129 
#define  LAPIC_TIMER_INTERRUPT 128 
 int lapic_interrupt_base ; 
 int /*<<< orphan*/ * lapic_intr_func ; 
 int /*<<< orphan*/  panic (char*,int,int /*<<< orphan*/ ) ; 

void
lapic_set_intr_func(int vector, i386_intr_func_t func)
{
	if (vector > lapic_interrupt_base)
		vector -= lapic_interrupt_base;

	switch (vector) {
	case LAPIC_NMI_INTERRUPT:
	case LAPIC_INTERPROCESSOR_INTERRUPT:
	case LAPIC_TIMER_INTERRUPT:
	case LAPIC_THERMAL_INTERRUPT:
	case LAPIC_PERFCNT_INTERRUPT:
	case LAPIC_CMCI_INTERRUPT:
	case LAPIC_PM_INTERRUPT:
		lapic_intr_func[vector] = func;
		break;
	default:
		panic("lapic_set_intr_func(%d,%p) invalid vector\n",
			vector, func);
	}
}