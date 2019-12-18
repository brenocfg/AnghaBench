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
struct spider_pic {int /*<<< orphan*/  host; scalar_t__ regs; } ;
struct irq_desc {TYPE_1__* chip; struct spider_pic* handler_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eoi ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned int NO_IRQ ; 
 unsigned int SPIDER_IRQ_INVALID ; 
 scalar_t__ TIR_CS ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int in_be32 (scalar_t__) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void spider_irq_cascade(unsigned int irq, struct irq_desc *desc)
{
	struct spider_pic *pic = desc->handler_data;
	unsigned int cs, virq;

	cs = in_be32(pic->regs + TIR_CS) >> 24;
	if (cs == SPIDER_IRQ_INVALID)
		virq = NO_IRQ;
	else
		virq = irq_linear_revmap(pic->host, cs);
	if (virq != NO_IRQ)
		generic_handle_irq(virq);
	desc->chip->eoi(irq);
}