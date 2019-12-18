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
struct irq_desc {TYPE_1__* action; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  (* handler ) (unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmbus_flow_handler(unsigned int irq, struct irq_desc *desc)
{
	kstat_incr_irqs_this_cpu(irq, desc);

	desc->action->handler(irq, desc->action->dev_id);
}