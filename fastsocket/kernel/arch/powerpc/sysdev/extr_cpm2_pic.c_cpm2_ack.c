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
struct TYPE_2__ {int /*<<< orphan*/  ic_sipnrh; } ;

/* Variables and functions */
 TYPE_1__* cpm2_intctl ; 
 int* irq_to_siubit ; 
 int* irq_to_siureg ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 unsigned int virq_to_hw (unsigned int) ; 

__attribute__((used)) static void cpm2_ack(unsigned int virq)
{
	int	bit, word;
	unsigned int irq_nr = virq_to_hw(virq);

	bit = irq_to_siubit[irq_nr];
	word = irq_to_siureg[irq_nr];

	out_be32(&cpm2_intctl->ic_sipnrh + word, 1 << bit);
}