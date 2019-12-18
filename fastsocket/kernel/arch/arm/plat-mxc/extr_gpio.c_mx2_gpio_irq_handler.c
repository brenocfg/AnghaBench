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
typedef  int u32 ;
struct mxc_gpio_port {scalar_t__ base; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_IMR ; 
 scalar_t__ GPIO_ISR ; 
 int __raw_readl (scalar_t__) ; 
 scalar_t__ get_irq_data (int) ; 
 int gpio_table_size ; 
 int /*<<< orphan*/  mxc_gpio_irq_handler (struct mxc_gpio_port*,int) ; 

__attribute__((used)) static void mx2_gpio_irq_handler(u32 irq, struct irq_desc *desc)
{
	int i;
	u32 irq_msk, irq_stat;
	struct mxc_gpio_port *port = (struct mxc_gpio_port *)get_irq_data(irq);

	/* walk through all interrupt status registers */
	for (i = 0; i < gpio_table_size; i++) {
		irq_msk = __raw_readl(port[i].base + GPIO_IMR);
		if (!irq_msk)
			continue;

		irq_stat = __raw_readl(port[i].base + GPIO_ISR) & irq_msk;
		if (irq_stat)
			mxc_gpio_irq_handler(&port[i], irq_stat);
	}
}