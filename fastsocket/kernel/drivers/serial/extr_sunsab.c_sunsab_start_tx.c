#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tx; } ;
struct TYPE_8__ {int fifosize; TYPE_2__ icount; TYPE_1__* state; } ;
struct uart_sunsab_port {int interrupt_mask1; TYPE_5__* regs; TYPE_3__ port; int /*<<< orphan*/  irqflags; } ;
struct uart_port {int dummy; } ;
struct circ_buf {int* buf; size_t tail; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmdr; int /*<<< orphan*/ * xfifo; int /*<<< orphan*/  imr1; } ;
struct TYPE_10__ {TYPE_4__ w; } ;
struct TYPE_6__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB82532_ALLS ; 
 int SAB82532_CMDR_XF ; 
 int SAB82532_IMR1_ALLS ; 
 int SAB82532_IMR1_XPR ; 
 int /*<<< orphan*/  SAB82532_XPR ; 
 int UART_XMIT_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunsab_cec_wait (struct uart_sunsab_port*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunsab_start_tx(struct uart_port *port)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	struct circ_buf *xmit = &up->port.state->xmit;
	int i;

	up->interrupt_mask1 &= ~(SAB82532_IMR1_ALLS|SAB82532_IMR1_XPR);
	writeb(up->interrupt_mask1, &up->regs->w.imr1);
	
	if (!test_bit(SAB82532_XPR, &up->irqflags))
		return;

	clear_bit(SAB82532_ALLS, &up->irqflags);
	clear_bit(SAB82532_XPR, &up->irqflags);

	for (i = 0; i < up->port.fifosize; i++) {
		writeb(xmit->buf[xmit->tail],
		       &up->regs->w.xfifo[i]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		if (uart_circ_empty(xmit))
			break;
	}

	/* Issue a Transmit Frame command.  */
	sunsab_cec_wait(up);
	writeb(SAB82532_CMDR_XF, &up->regs->w.cmdr);
}