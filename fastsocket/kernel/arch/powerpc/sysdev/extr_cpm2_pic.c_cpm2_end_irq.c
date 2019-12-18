#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ic_simrh; } ;
struct TYPE_3__ {int status; scalar_t__ action; } ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int IRQ_INPROGRESS ; 
 TYPE_2__* cpm2_intctl ; 
 TYPE_1__* irq_desc ; 
 int* irq_to_siubit ; 
 int* irq_to_siureg ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int* ppc_cached_irq_mask ; 
 unsigned int virq_to_hw (unsigned int) ; 

__attribute__((used)) static void cpm2_end_irq(unsigned int virq)
{
	int	bit, word;
	unsigned int irq_nr = virq_to_hw(virq);

	if (!(irq_desc[irq_nr].status & (IRQ_DISABLED|IRQ_INPROGRESS))
			&& irq_desc[irq_nr].action) {

		bit = irq_to_siubit[irq_nr];
		word = irq_to_siureg[irq_nr];

		ppc_cached_irq_mask[word] |= 1 << bit;
		out_be32(&cpm2_intctl->ic_simrh + word, ppc_cached_irq_mask[word]);

		/*
		 * Work around large numbers of spurious IRQs on PowerPC 82xx
		 * systems.
		 */
		mb();
	}
}