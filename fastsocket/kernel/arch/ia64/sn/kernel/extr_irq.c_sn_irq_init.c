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
struct irq_desc {int /*<<< orphan*/ * chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_SN2_FIRST_DEVICE_VECTOR ; 
 int /*<<< orphan*/  IA64_SN2_LAST_DEVICE_VECTOR ; 
 int NR_IRQS ; 
 int /*<<< orphan*/  ia64_first_device_vector ; 
 int /*<<< orphan*/  ia64_last_device_vector ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  irq_type_sn ; 
 int /*<<< orphan*/  no_irq_chip ; 

void sn_irq_init(void)
{
	int i;
	struct irq_desc *base_desc = irq_desc;

	ia64_first_device_vector = IA64_SN2_FIRST_DEVICE_VECTOR;
	ia64_last_device_vector = IA64_SN2_LAST_DEVICE_VECTOR;

	for (i = 0; i < NR_IRQS; i++) {
		if (base_desc[i].chip == &no_irq_chip) {
			base_desc[i].chip = &irq_type_sn;
		}
	}
}