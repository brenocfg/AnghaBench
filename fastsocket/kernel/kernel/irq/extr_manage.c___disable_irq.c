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
struct irq_desc {TYPE_2__* chip; int /*<<< orphan*/  status; int /*<<< orphan*/  depth; TYPE_1__* action; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (unsigned int) ;} ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int IRQF_NO_SUSPEND ; 
 int IRQF_TIMER ; 
 int /*<<< orphan*/  IRQ_DISABLED ; 
 int /*<<< orphan*/  IRQ_SUSPENDED ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

void __disable_irq(struct irq_desc *desc, unsigned int irq, bool suspend)
{
	if (suspend) {
		/* kABI WARNING! We cannot change IRQF_TIMER to include
		   IRQF_NO_SUSPEND. So test for both bits here. */
		if (!desc->action ||
		    (desc->action->flags & (IRQF_TIMER|IRQF_NO_SUSPEND)))
			return;
		desc->status |= IRQ_SUSPENDED;
	}

	if (!desc->depth++) {
		desc->status |= IRQ_DISABLED;
		desc->chip->disable(irq);
	}
}