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
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_GPIO_REG (int /*<<< orphan*/ ) ; 
 int IRQ_TYPE_EDGE_BOTH ; 
 int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eoi_register_offset ; 
 int /*<<< orphan*/  ep93xx_gpio_update_int_params (int) ; 
 int* gpio_int_type2 ; 
 int* gpio_int_unmasked ; 
 TYPE_1__* irq_desc ; 
 int irq_to_gpio (unsigned int) ; 

__attribute__((used)) static void ep93xx_gpio_irq_mask_ack(unsigned int irq)
{
	int line = irq_to_gpio(irq);
	int port = line >> 3;
	int port_mask = 1 << (line & 7);

	if ((irq_desc[irq].status & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH)
		gpio_int_type2[port] ^= port_mask; /* switch edge direction */

	gpio_int_unmasked[port] &= ~port_mask;
	ep93xx_gpio_update_int_params(port);

	__raw_writeb(port_mask, EP93XX_GPIO_REG(eoi_register_offset[port]));
}