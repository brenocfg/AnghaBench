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
struct irq_desc {int status; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (int) ;int /*<<< orphan*/  (* mask ) (int) ;} ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int IRQ_MOVE_PENDING ; 
 struct irq_desc* irq_to_desc (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  move_masked_irq (int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 scalar_t__ unlikely (int) ; 

void move_native_irq(int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);

	if (likely(!(desc->status & IRQ_MOVE_PENDING)))
		return;

	if (unlikely(desc->status & IRQ_DISABLED))
		return;

	desc->chip->mask(irq);
	move_masked_irq(irq);
	desc->chip->unmask(irq);
}