#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mxc_gpio_port {int virtual_irq_start; int both_edges; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* handle_irq ) (int,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* irq_desc ; 
 int irq_to_gpio (int) ; 
 int /*<<< orphan*/  mxc_flip_edge (struct mxc_gpio_port*,int) ; 
 int /*<<< orphan*/  stub1 (int,TYPE_1__*) ; 

__attribute__((used)) static void mxc_gpio_irq_handler(struct mxc_gpio_port *port, u32 irq_stat)
{
	u32 gpio_irq_no;

	gpio_irq_no = port->virtual_irq_start;
	for (; irq_stat != 0; irq_stat >>= 1, gpio_irq_no++) {
		u32 gpio = irq_to_gpio(gpio_irq_no);

		if ((irq_stat & 1) == 0)
			continue;

		BUG_ON(!(irq_desc[gpio_irq_no].handle_irq));

		if (port->both_edges & (1 << (gpio & 31)))
			mxc_flip_edge(port, gpio);

		irq_desc[gpio_irq_no].handle_irq(gpio_irq_no,
				&irq_desc[gpio_irq_no]);
	}
}