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
struct irq_desc {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  lapic_chip ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void lapic_register_intr(int irq, struct irq_desc *desc)
{
	desc->status &= ~IRQ_LEVEL;
	set_irq_chip_and_handler_name(irq, &lapic_chip, handle_edge_irq,
				      "edge");
}