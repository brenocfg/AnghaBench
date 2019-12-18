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
struct TYPE_6__ {int rx; } ;
struct uart_port {scalar_t__ type; TYPE_3__ icount; int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct sci_port {scalar_t__ break_flag; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_SCI ; 
 int /*<<< orphan*/  SCxRDR ; 
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_FER (struct uart_port*) ; 
 unsigned short SCxSR_PER (struct uart_port*) ; 
 unsigned short SCxSR_RDxF (struct uart_port*) ; 
 int /*<<< orphan*/  SCxSR_RDxF_CLEAR (struct uart_port*) ; 
 scalar_t__ STEPFN (char) ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_PARITY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 void* sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sci_rxroom (struct uart_port*) ; 
 int scif_rxroom (struct uart_port*) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 
 int tty_buffer_request_room (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char,unsigned char) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,char) ; 

__attribute__((used)) static inline void sci_receive_chars(struct uart_port *port)
{
	struct sci_port *sci_port = to_sci_port(port);
	struct tty_struct *tty = port->state->port.tty;
	int i, count, copied = 0;
	unsigned short status;
	unsigned char flag;

	status = sci_in(port, SCxSR);
	if (!(status & SCxSR_RDxF(port)))
		return;

	while (1) {
		if (port->type == PORT_SCI)
			count = sci_rxroom(port);
		else
			count = scif_rxroom(port);

		/* Don't copy more bytes than there is room for in the buffer */
		count = tty_buffer_request_room(tty, count);

		/* If for any reason we can't copy more data, we're done! */
		if (count == 0)
			break;

		if (port->type == PORT_SCI) {
			char c = sci_in(port, SCxRDR);
			if (uart_handle_sysrq_char(port, c) ||
			    sci_port->break_flag)
				count = 0;
			else
				tty_insert_flip_char(tty, c, TTY_NORMAL);
		} else {
			for (i = 0; i < count; i++) {
				char c = sci_in(port, SCxRDR);
				status = sci_in(port, SCxSR);
#if defined(CONFIG_CPU_SH3)
				/* Skip "chars" during break */
				if (sci_port->break_flag) {
					if ((c == 0) &&
					    (status & SCxSR_FER(port))) {
						count--; i--;
						continue;
					}

					/* Nonzero => end-of-break */
					dev_dbg(port->dev, "debounce<%02x>\n", c);
					sci_port->break_flag = 0;

					if (STEPFN(c)) {
						count--; i--;
						continue;
					}
				}
#endif /* CONFIG_CPU_SH3 */
				if (uart_handle_sysrq_char(port, c)) {
					count--; i--;
					continue;
				}

				/* Store data and status */
				if (status&SCxSR_FER(port)) {
					flag = TTY_FRAME;
					dev_notice(port->dev, "frame error\n");
				} else if (status&SCxSR_PER(port)) {
					flag = TTY_PARITY;
					dev_notice(port->dev, "parity error\n");
				} else
					flag = TTY_NORMAL;

				tty_insert_flip_char(tty, c, flag);
			}
		}

		sci_in(port, SCxSR); /* dummy read */
		sci_out(port, SCxSR, SCxSR_RDxF_CLEAR(port));

		copied += count;
		port->icount.rx += count;
	}

	if (copied) {
		/* Tell the rest of the system the news. New characters! */
		tty_flip_buffer_push(tty);
	} else {
		sci_in(port, SCxSR); /* dummy read */
		sci_out(port, SCxSR, SCxSR_RDxF_CLEAR(port));
	}
}