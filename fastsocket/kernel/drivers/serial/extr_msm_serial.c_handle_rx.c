#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  overrun; } ;
struct uart_port {unsigned int read_status_mask; TYPE_3__ icount; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 int /*<<< orphan*/  UART_CR ; 
 int /*<<< orphan*/  UART_CR_CMD_RESET_ERR ; 
 int /*<<< orphan*/  UART_RF ; 
 int /*<<< orphan*/  UART_SR ; 
 int UART_SR_OVERRUN ; 
 unsigned int UART_SR_PAR_FRAME_ERR ; 
 unsigned int UART_SR_RX_BREAK ; 
 unsigned int UART_SR_RX_READY ; 
 int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned int,char) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 int /*<<< orphan*/  uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void handle_rx(struct uart_port *port)
{
	struct tty_struct *tty = port->state->port.tty;
	unsigned int sr;

	/*
	 * Handle overrun. My understanding of the hardware is that overrun
	 * is not tied to the RX buffer, so we handle the case out of band.
	 */
	if ((msm_read(port, UART_SR) & UART_SR_OVERRUN)) {
		port->icount.overrun++;
		tty_insert_flip_char(tty, 0, TTY_OVERRUN);
		msm_write(port, UART_CR_CMD_RESET_ERR, UART_CR);
	}

	/* and now the main RX loop */
	while ((sr = msm_read(port, UART_SR)) & UART_SR_RX_READY) {
		unsigned int c;
		char flag = TTY_NORMAL;

		c = msm_read(port, UART_RF);

		if (sr & UART_SR_RX_BREAK) {
			port->icount.brk++;
			if (uart_handle_break(port))
				continue;
		} else if (sr & UART_SR_PAR_FRAME_ERR) {
			port->icount.frame++;
		} else {
			port->icount.rx++;
		}

		/* Mask conditions we're ignorning. */
		sr &= port->read_status_mask;

		if (sr & UART_SR_RX_BREAK) {
			flag = TTY_BREAK;
		} else if (sr & UART_SR_PAR_FRAME_ERR) {
			flag = TTY_FRAME;
		}

		if (!uart_handle_sysrq_char(port, c))
			tty_insert_flip_char(tty, c, flag);
	}

	tty_flip_buffer_push(tty);
}