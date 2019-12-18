#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uart_port {scalar_t__ uartclk; int flags; size_t type; scalar_t__ serial_out; scalar_t__ serial_in; scalar_t__ dev; int /*<<< orphan*/  private_data; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  regshift; int /*<<< orphan*/  fifosize; int /*<<< orphan*/  irqflags; int /*<<< orphan*/  irq; int /*<<< orphan*/  membase; int /*<<< orphan*/  iobase; } ;
struct TYPE_5__ {scalar_t__ uartclk; int flags; size_t type; int line; scalar_t__ serial_out; scalar_t__ serial_in; int /*<<< orphan*/  fifosize; scalar_t__ dev; int /*<<< orphan*/  private_data; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  regshift; int /*<<< orphan*/  irqflags; int /*<<< orphan*/  irq; int /*<<< orphan*/  membase; int /*<<< orphan*/  iobase; } ;
struct uart_8250_port {TYPE_1__ port; int /*<<< orphan*/  tx_loadsz; int /*<<< orphan*/  capabilities; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_loadsz; int /*<<< orphan*/  flags; int /*<<< orphan*/  fifo_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_TYPE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uart_8250_port* serial8250_find_match_or_unused (struct uart_port*) ; 
 int /*<<< orphan*/  serial8250_reg ; 
 int /*<<< orphan*/  serial_mutex ; 
 int /*<<< orphan*/  set_io_from_upio (TYPE_1__*) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* uart_config ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

int serial8250_register_port(struct uart_port *port)
{
	struct uart_8250_port *uart;
	int ret = -ENOSPC;

	if (port->uartclk == 0)
		return -EINVAL;

	mutex_lock(&serial_mutex);

	uart = serial8250_find_match_or_unused(port);
	if (uart) {
		uart_remove_one_port(&serial8250_reg, &uart->port);

		uart->port.iobase       = port->iobase;
		uart->port.membase      = port->membase;
		uart->port.irq          = port->irq;
		uart->port.irqflags     = port->irqflags;
		uart->port.uartclk      = port->uartclk;
		uart->port.fifosize     = port->fifosize;
		uart->port.regshift     = port->regshift;
		uart->port.iotype       = port->iotype;
		uart->port.flags        = port->flags | UPF_BOOT_AUTOCONF;
		uart->port.mapbase      = port->mapbase;
		uart->port.private_data = port->private_data;
		if (port->dev)
			uart->port.dev = port->dev;

		if (port->flags & UPF_FIXED_TYPE) {
			uart->port.type = port->type;
			uart->port.fifosize = uart_config[port->type].fifo_size;
			uart->capabilities = uart_config[port->type].flags;
			uart->tx_loadsz = uart_config[port->type].tx_loadsz;
		}

		set_io_from_upio(&uart->port);
		/* Possibly override default I/O functions.  */
		if (port->serial_in)
			uart->port.serial_in = port->serial_in;
		if (port->serial_out)
			uart->port.serial_out = port->serial_out;

		ret = uart_add_one_port(&serial8250_reg, &uart->port);
		if (ret == 0)
			ret = uart->port.line;
	}
	mutex_unlock(&serial_mutex);

	return ret;
}