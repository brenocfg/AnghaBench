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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_free_chip_data (struct irq_desc*,struct irq_desc*) ; 
 int /*<<< orphan*/  free_desc_masks (struct irq_desc*,struct irq_desc*) ; 
 int /*<<< orphan*/  free_kstat_irqs (struct irq_desc*,struct irq_desc*) ; 

__attribute__((used)) static void free_one_irq_desc(struct irq_desc *old_desc, struct irq_desc *desc)
{
	free_kstat_irqs(old_desc, desc);
	free_desc_masks(old_desc, desc);
	arch_free_chip_data(old_desc, desc);
}