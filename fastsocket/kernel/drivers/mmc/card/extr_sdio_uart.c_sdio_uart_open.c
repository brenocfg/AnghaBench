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
struct tty_struct {struct sdio_uart_port* driver_data; int /*<<< orphan*/  index; } ;
struct sdio_uart_port {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  opened; struct tty_struct* tty; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sdio_uart_port* sdio_uart_port_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_port_put (struct sdio_uart_port*) ; 
 int sdio_uart_startup (struct sdio_uart_port*) ; 

__attribute__((used)) static int sdio_uart_open (struct tty_struct *tty, struct file * filp)
{
	struct sdio_uart_port *port;
	int ret;

	port = sdio_uart_port_get(tty->index);
	if (!port)
		return -ENODEV;

	mutex_lock(&port->open_lock);

	/*
	 * Make sure not to mess up with a dead port
	 * which has not been closed yet.
	 */
	if (tty->driver_data && tty->driver_data != port) {
		mutex_unlock(&port->open_lock);
		sdio_uart_port_put(port);
		return -EBUSY;
	}

	if (!port->opened) {
		tty->driver_data = port;
		port->tty = tty;
		ret = sdio_uart_startup(port);
		if (ret) {
			tty->driver_data = NULL;
			port->tty = NULL;
			mutex_unlock(&port->open_lock);
			sdio_uart_port_put(port);
			return ret;
		}
	}
	port->opened++;
	mutex_unlock(&port->open_lock);
	return 0;
}