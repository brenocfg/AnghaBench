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
typedef  int /*<<< orphan*/  u32 ;
struct irq_desc {scalar_t__ handle_irq; } ;

/* Variables and functions */
 scalar_t__ handle_edge_irq ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  irq_to_gpio (unsigned int) ; 
 int /*<<< orphan*/  set_gpio_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_maska (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_gpio_mask_ack_irq(unsigned int irq)
{
	struct irq_desc *desc = irq_desc + irq;
	u32 gpionr = irq_to_gpio(irq);

	if (desc->handle_irq == handle_edge_irq)
		set_gpio_data(gpionr, 0);

	set_gpio_maska(gpionr, 0);
}