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
struct tty_struct {TYPE_1__* termios; struct esp_struct* driver_data; } ;
struct ktermios {int c_cflag; } ;
struct esp_struct {int MCR; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CBAUD ; 
 int CRTSCTS ; 
 int ESI_WRITE_UART ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_CMD2 ; 
 int UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  change_speed (struct esp_struct*) ; 
 int /*<<< orphan*/  rs_start (struct tty_struct*) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rs_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	struct esp_struct *info = tty->driver_data;
	unsigned long flags;

	change_speed(info);

	spin_lock_irqsave(&info->lock, flags);

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) &&
		!(tty->termios->c_cflag & CBAUD)) {
		info->MCR &= ~(UART_MCR_DTR|UART_MCR_RTS);
		serial_out(info, UART_ESI_CMD1, ESI_WRITE_UART);
		serial_out(info, UART_ESI_CMD2, UART_MCR);
		serial_out(info, UART_ESI_CMD2, info->MCR);
	}

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) &&
		(tty->termios->c_cflag & CBAUD)) {
		info->MCR |= (UART_MCR_DTR | UART_MCR_RTS);
		serial_out(info, UART_ESI_CMD1, ESI_WRITE_UART);
		serial_out(info, UART_ESI_CMD2, UART_MCR);
		serial_out(info, UART_ESI_CMD2, info->MCR);
	}

	spin_unlock_irqrestore(&info->lock, flags);

	/* Handle turning of CRTSCTS */
	if ((old_termios->c_cflag & CRTSCTS) &&
	    !(tty->termios->c_cflag & CRTSCTS)) {
		rs_start(tty);
	}
}