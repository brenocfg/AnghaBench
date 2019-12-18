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
 unsigned int TC6393XB_NR_IRQS ; 
 struct tc6393xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  set_irq_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_flags (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc6393xb_detach_irq(struct platform_device *dev)
{
	struct tc6393xb *tc6393xb = platform_get_drvdata(dev);
	unsigned int irq, irq_base;

	set_irq_chained_handler(tc6393xb->irq, NULL);
	set_irq_data(tc6393xb->irq, NULL);

	irq_base = tc6393xb->irq_base;

	for (irq = irq_base; irq < irq_base + TC6393XB_NR_IRQS; irq++) {
		set_irq_flags(irq, 0);
		set_irq_chip(irq, NULL);
		set_irq_chip_data(irq, NULL);
	}
}