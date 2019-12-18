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
typedef  enum ixp23xx_irq_type { ____Placeholder_ixp23xx_irq_type } ixp23xx_irq_type ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_VALID ; 
#define  IXP23XX_IRQ_EDGE 129 
#define  IXP23XX_IRQ_LEVEL 128 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  ixp23xx_irq_edge_chip ; 
 int /*<<< orphan*/  ixp23xx_irq_level_chip ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_handler (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixp23xx_config_irq(unsigned int irq, enum ixp23xx_irq_type type)
{
	switch (type) {
	case IXP23XX_IRQ_LEVEL:
		set_irq_chip(irq, &ixp23xx_irq_level_chip);
		set_irq_handler(irq, handle_level_irq);
		break;
	case IXP23XX_IRQ_EDGE:
		set_irq_chip(irq, &ixp23xx_irq_edge_chip);
		set_irq_handler(irq, handle_edge_irq);
		break;
	}
	set_irq_flags(irq, IRQF_VALID);
}