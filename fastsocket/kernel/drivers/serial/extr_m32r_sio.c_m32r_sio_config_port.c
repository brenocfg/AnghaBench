#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t type; int /*<<< orphan*/  lock; int /*<<< orphan*/  fifosize; } ;
struct uart_sio_port {TYPE_1__ port; } ;
struct uart_port {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dfl_xmit_fifo_size; } ;

/* Variables and functions */
 size_t PORT_M32R_BASE ; 
 size_t PORT_M32R_SIO ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* uart_config ; 

__attribute__((used)) static void m32r_sio_config_port(struct uart_port *port, int flags)
{
	struct uart_sio_port *up = (struct uart_sio_port *)port;

	spin_lock_irqsave(&up->port.lock, flags);

	up->port.type = (PORT_M32R_SIO - PORT_M32R_BASE + 1);
	up->port.fifosize = uart_config[up->port.type].dfl_xmit_fifo_size;

	spin_unlock_irqrestore(&up->port.lock, flags);
}