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
struct tty_struct {struct sdio_uart_port* driver_data; } ;
struct sdio_uart_port {int mctrl; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int sdio_uart_get_mctrl (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 

__attribute__((used)) static int sdio_uart_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct sdio_uart_port *port = tty->driver_data;
	int result;

	result = sdio_uart_claim_func(port);
	if (!result) {
		result = port->mctrl | sdio_uart_get_mctrl(port);
		sdio_uart_release_func(port);
	}

	return result;
}