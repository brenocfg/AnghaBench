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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack ) (int) ;} ;

/* Variables and functions */
 int IRQ_ISA ; 
 int /*<<< orphan*/  bast_pc104_mask (unsigned int) ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
bast_pc104_maskack(unsigned int irqno)
{
	struct irq_desc *desc = irq_desc + IRQ_ISA;

	bast_pc104_mask(irqno);
	desc->chip->ack(IRQ_ISA);
}