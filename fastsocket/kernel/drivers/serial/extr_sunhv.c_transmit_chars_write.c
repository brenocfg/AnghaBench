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
struct TYPE_2__ {unsigned long tx; } ;
struct uart_port {TYPE_1__ icount; } ;
struct circ_buf {unsigned long tail; int /*<<< orphan*/  head; scalar_t__ buf; } ;

/* Variables and functions */
 unsigned long CIRC_CNT_TO_END (int /*<<< orphan*/ ,unsigned long,int) ; 
 unsigned long HV_EOK ; 
 int UART_XMIT_SIZE ; 
 unsigned long __pa (scalar_t__) ; 
 unsigned long sun4v_con_write (unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  uart_circ_empty (struct circ_buf*) ; 

__attribute__((used)) static void transmit_chars_write(struct uart_port *port, struct circ_buf *xmit)
{
	while (!uart_circ_empty(xmit)) {
		unsigned long ra = __pa(xmit->buf + xmit->tail);
		unsigned long len, status, sent;

		len = CIRC_CNT_TO_END(xmit->head, xmit->tail,
				      UART_XMIT_SIZE);
		status = sun4v_con_write(ra, len, &sent);
		if (status != HV_EOK)
			break;
		xmit->tail = (xmit->tail + sent) & (UART_XMIT_SIZE - 1);
		port->icount.tx += sent;
	}
}