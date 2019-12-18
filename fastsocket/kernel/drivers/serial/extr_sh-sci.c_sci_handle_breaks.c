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
struct uart_port {int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct sci_port {int break_flag; } ;
struct TYPE_3__ {struct tty_struct* tty; } ;
struct TYPE_4__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_BRK (struct uart_port*) ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sci_handle_fifo_overrun (struct uart_port*) ; 
 unsigned short sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ tty_insert_flip_char (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 

__attribute__((used)) static inline int sci_handle_breaks(struct uart_port *port)
{
	int copied = 0;
	unsigned short status = sci_in(port, SCxSR);
	struct tty_struct *tty = port->state->port.tty;
	struct sci_port *s = to_sci_port(port);

	if (uart_handle_break(port))
		return 0;

	if (!s->break_flag && status & SCxSR_BRK(port)) {
#if defined(CONFIG_CPU_SH3)
		/* Debounce break */
		s->break_flag = 1;
#endif
		/* Notify of BREAK */
		if (tty_insert_flip_char(tty, 0, TTY_BREAK))
			copied++;

		dev_dbg(port->dev, "BREAK detected\n");
	}

	if (copied)
		tty_flip_buffer_push(tty);

	copied += sci_handle_fifo_overrun(port);

	return copied;
}