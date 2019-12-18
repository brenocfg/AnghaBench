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
struct irq_desc {int /*<<< orphan*/ * kstat_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_kstat_irqs(struct irq_desc *old_desc, struct irq_desc *desc)
{
	if (old_desc->kstat_irqs == desc->kstat_irqs)
		return;

	kfree(old_desc->kstat_irqs);
	old_desc->kstat_irqs = NULL;
}