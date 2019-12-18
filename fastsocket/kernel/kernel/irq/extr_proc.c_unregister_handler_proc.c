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
struct irqaction {TYPE_1__* dir; } ;
struct irq_desc {int /*<<< orphan*/  dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void unregister_handler_proc(unsigned int irq, struct irqaction *action)
{
	if (action->dir) {
		struct irq_desc *desc = irq_to_desc(irq);

		remove_proc_entry(action->dir->name, desc->dir);
	}
}