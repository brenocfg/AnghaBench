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
struct uart_port {int dummy; } ;
struct circ_buf {size_t head; scalar_t__ buf; int /*<<< orphan*/  tail; } ;
struct atmel_uart_port {struct circ_buf rx_ring; } ;
struct atmel_uart_char {unsigned int status; unsigned int ch; } ;

/* Variables and functions */
 int ATMEL_SERIAL_RINGSIZE ; 
 int /*<<< orphan*/  CIRC_SPACE (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void
atmel_buffer_rx_char(struct uart_port *port, unsigned int status,
		     unsigned int ch)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct circ_buf *ring = &atmel_port->rx_ring;
	struct atmel_uart_char *c;

	if (!CIRC_SPACE(ring->head, ring->tail, ATMEL_SERIAL_RINGSIZE))
		/* Buffer overflow, ignore char */
		return;

	c = &((struct atmel_uart_char *)ring->buf)[ring->head];
	c->status	= status;
	c->ch		= ch;

	/* Make sure the character is stored before we update head. */
	smp_wmb();

	ring->head = (ring->head + 1) & (ATMEL_SERIAL_RINGSIZE - 1);
}