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
struct vuart_bus_priv {int /*<<< orphan*/ * devices; TYPE_1__* bmp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int PORT_COUNT ; 
 int __ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_ports_bmp (TYPE_1__*) ; 
 int /*<<< orphan*/  ps3_vuart_handle_port_interrupt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ps3_vuart_irq_handler(int irq, void *_private)
{
	struct vuart_bus_priv *bus_priv = _private;

	BUG_ON(!bus_priv);

	while (1) {
		unsigned int port;

		dump_ports_bmp(bus_priv->bmp);

		port = (BITS_PER_LONG - 1) - __ilog2(bus_priv->bmp->status);

		if (port == BITS_PER_LONG)
			break;

		BUG_ON(port >= PORT_COUNT);
		BUG_ON(!bus_priv->devices[port]);

		ps3_vuart_handle_port_interrupt(bus_priv->devices[port]);
	}

	return IRQ_HANDLED;
}