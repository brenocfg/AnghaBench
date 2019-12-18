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
struct tc6393xb {unsigned int irq_base; int /*<<< orphan*/  irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int IRQF_PROBE ; 
 int IRQF_VALID ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 unsigned int TC6393XB_NR_IRQS ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 struct tc6393xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  set_irq_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_chip_data (unsigned int,struct tc6393xb*) ; 
 int /*<<< orphan*/  set_irq_data (int /*<<< orphan*/ ,struct tc6393xb*) ; 
 int /*<<< orphan*/  set_irq_flags (unsigned int,int) ; 
 int /*<<< orphan*/  set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc6393xb_chip ; 
 int /*<<< orphan*/  tc6393xb_irq ; 

__attribute__((used)) static void tc6393xb_attach_irq(struct platform_device *dev)
{
	struct tc6393xb *tc6393xb = platform_get_drvdata(dev);
	unsigned int irq, irq_base;

	irq_base = tc6393xb->irq_base;

	for (irq = irq_base; irq < irq_base + TC6393XB_NR_IRQS; irq++) {
		set_irq_chip(irq, &tc6393xb_chip);
		set_irq_chip_data(irq, tc6393xb);
		set_irq_handler(irq, handle_edge_irq);
		set_irq_flags(irq, IRQF_VALID | IRQF_PROBE);
	}

	set_irq_type(tc6393xb->irq, IRQ_TYPE_EDGE_FALLING);
	set_irq_data(tc6393xb->irq, tc6393xb);
	set_irq_chained_handler(tc6393xb->irq, tc6393xb_irq);
}