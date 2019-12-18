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
struct seq_file {int dummy; } ;
struct irq_node {int /*<<< orphan*/  devname; struct irq_node* next; } ;
struct irq_controller {int /*<<< orphan*/  name; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * irqs; } ;

/* Variables and functions */
 struct irq_controller** irq_controller ; 
 struct irq_node** irq_list ; 
 TYPE_1__ kstat_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

int show_interrupts(struct seq_file *p, void *v)
{
	struct irq_controller *contr;
	struct irq_node *node;
	int i = *(loff_t *) v;

	/* autovector interrupts */
	if (irq_list[i]) {
		contr = irq_controller[i];
		node = irq_list[i];
		seq_printf(p, "%-8s %3u: %10u %s", contr->name, i, kstat_cpu(0).irqs[i], node->devname);
		while ((node = node->next))
			seq_printf(p, ", %s", node->devname);
		seq_puts(p, "\n");
	}
	return 0;
}