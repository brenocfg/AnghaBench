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
struct uart_port {scalar_t__ type; int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_3__ {struct tty_struct* tty; } ;
struct TYPE_4__ {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIF ; 
 int SCIF_ORER ; 
 int /*<<< orphan*/  SCLSR ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 int sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sci_handle_fifo_overrun(struct uart_port *port)
{
	struct tty_struct *tty = port->state->port.tty;
	int copied = 0;

	if (port->type != PORT_SCIF)
		return 0;

	if ((sci_in(port, SCLSR) & SCIF_ORER) != 0) {
		sci_out(port, SCLSR, 0);

		tty_insert_flip_char(tty, 0, TTY_OVERRUN);
		tty_flip_buffer_push(tty);

		dev_notice(port->dev, "overrun error\n");
		copied++;
	}

	return copied;
}