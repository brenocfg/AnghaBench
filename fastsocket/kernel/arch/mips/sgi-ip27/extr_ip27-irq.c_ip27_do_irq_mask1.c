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
struct slice_data {int* level_to_irq; } ;
typedef  int /*<<< orphan*/  hubreg_t ;
typedef  size_t cpuid_t ;
struct TYPE_2__ {struct slice_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_HUB_CLR_INTR (int) ; 
 int /*<<< orphan*/  LOCAL_HUB_L (int) ; 
 int PI_INT_MASK1_A ; 
 int PI_INT_MASK1_B ; 
 int PI_INT_PEND1 ; 
 TYPE_1__* cpu_data ; 
 scalar_t__ cputoslice (size_t) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int ms1bit (int /*<<< orphan*/ ) ; 
 size_t smp_processor_id () ; 

__attribute__((used)) static void ip27_do_irq_mask1(void)
{
	int irq, swlevel;
	hubreg_t pend1, mask1;
	cpuid_t cpu = smp_processor_id();
	int pi_int_mask1 = (cputoslice(cpu) == 0) ?  PI_INT_MASK1_A : PI_INT_MASK1_B;
	struct slice_data *si = cpu_data[cpu].data;

	/* copied from Irix intpend0() */
	pend1 = LOCAL_HUB_L(PI_INT_PEND1);
	mask1 = LOCAL_HUB_L(pi_int_mask1);

	pend1 &= mask1;		/* Pick intrs we should look at */
	if (!pend1)
		return;

	swlevel = ms1bit(pend1);
	/* "map" swlevel to irq */
	irq = si->level_to_irq[swlevel];
	LOCAL_HUB_CLR_INTR(swlevel);
	do_IRQ(irq);

	LOCAL_HUB_L(PI_INT_PEND1);
}