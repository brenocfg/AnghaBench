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
struct irq_desc {scalar_t__ irq; int node; } ;

/* Variables and functions */
 scalar_t__ NR_IRQS_LEGACY ; 
 struct irq_desc* __real_move_irq_desc (struct irq_desc*,int) ; 

struct irq_desc *move_irq_desc(struct irq_desc *desc, int node)
{
	/* those static or target node is -1, do not move them */
	if (desc->irq < NR_IRQS_LEGACY || node == -1)
		return desc;

	if (desc->node != node)
		desc = __real_move_irq_desc(desc, node);

	return desc;
}