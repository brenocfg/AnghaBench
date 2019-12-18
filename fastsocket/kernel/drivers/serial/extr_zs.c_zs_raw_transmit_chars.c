#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct TYPE_7__ {TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct zs_port {TYPE_3__ port; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  write_zsdata (struct zs_port*,scalar_t__) ; 
 int /*<<< orphan*/  zs_raw_stop_tx (struct zs_port*) ; 

__attribute__((used)) static void zs_raw_transmit_chars(struct zs_port *zport)
{
	struct circ_buf *xmit = &zport->port.state->xmit;

	/* XON/XOFF chars.  */
	if (zport->port.x_char) {
		write_zsdata(zport, zport->port.x_char);
		zport->port.icount.tx++;
		zport->port.x_char = 0;
		return;
	}

	/* If nothing to do or stopped or hardware stopped.  */
	if (uart_circ_empty(xmit) || uart_tx_stopped(&zport->port)) {
		zs_raw_stop_tx(zport);
		return;
	}

	/* Send char.  */
	write_zsdata(zport, xmit->buf[xmit->tail]);
	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	zport->port.icount.tx++;

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&zport->port);

	/* Are we are done?  */
	if (uart_circ_empty(xmit))
		zs_raw_stop_tx(zport);
}