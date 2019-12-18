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
struct TYPE_2__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_1__ icount; } ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 long HV_EOK ; 
 int UART_XMIT_SIZE ; 
 long sun4v_con_putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 

__attribute__((used)) static void transmit_chars_putchar(struct uart_port *port, struct circ_buf *xmit)
{
	while (!uart_circ_empty(xmit)) {
		long status = sun4v_con_putchar(xmit->buf[xmit->tail]);

		if (status != HV_EOK)
			break;

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}
}