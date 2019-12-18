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
struct tty_struct {scalar_t__ count; int closing; struct sdio_uart_port* driver_data; } ;
struct sdio_uart_port {scalar_t__ opened; int /*<<< orphan*/  open_lock; int /*<<< orphan*/ * tty; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_uart_port_put (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_shutdown (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 

__attribute__((used)) static void sdio_uart_close(struct tty_struct *tty, struct file * filp)
{
	struct sdio_uart_port *port = tty->driver_data;

	if (!port)
		return;

	mutex_lock(&port->open_lock);
	BUG_ON(!port->opened);

	/*
	 * This is messy.  The tty layer calls us even when open()
	 * returned an error.  Ignore this close request if tty->count
	 * is larger than port->count.
	 */
	if (tty->count > port->opened) {
		mutex_unlock(&port->open_lock);
		return;
	}

	if (--port->opened == 0) {
		tty->closing = 1;
		sdio_uart_shutdown(port);
		tty_ldisc_flush(tty);
		port->tty = NULL;
		tty->driver_data = NULL;
		tty->closing = 0;
	}
	mutex_unlock(&port->open_lock);
	sdio_uart_port_put(port);
}