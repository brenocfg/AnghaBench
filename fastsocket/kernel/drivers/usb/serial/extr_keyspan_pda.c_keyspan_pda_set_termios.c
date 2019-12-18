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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct tty_struct {int /*<<< orphan*/  termios; } ;
struct ktermios {int dummy; } ;
typedef  scalar_t__ speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 scalar_t__ keyspan_pda_setbaud (struct usb_serial*,scalar_t__) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,scalar_t__,scalar_t__) ; 
 scalar_t__ tty_get_baud_rate (struct tty_struct*) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_copy_hw (int /*<<< orphan*/ ,struct ktermios*) ; 

__attribute__((used)) static void keyspan_pda_set_termios(struct tty_struct *tty,
		struct usb_serial_port *port, struct ktermios *old_termios)
{
	struct usb_serial *serial = port->serial;
	speed_t speed;

	/* cflag specifies lots of stuff: number of stop bits, parity, number
	   of data bits, baud. What can the device actually handle?:
	   CSTOPB (1 stop bit or 2)
	   PARENB (parity)
	   CSIZE (5bit .. 8bit)
	   There is minimal hw support for parity (a PSW bit seems to hold the
	   parity of whatever is in the accumulator). The UART either deals
	   with 10 bits (start, 8 data, stop) or 11 bits (start, 8 data,
	   1 special, stop). So, with firmware changes, we could do:
	   8N1: 10 bit
	   8N2: 11 bit, extra bit always (mark?)
	   8[EOMS]1: 11 bit, extra bit is parity
	   7[EOMS]1: 10 bit, b0/b7 is parity
	   7[EOMS]2: 11 bit, b0/b7 is parity, extra bit always (mark?)

	   HW flow control is dictated by the tty->termios->c_cflags & CRTSCTS
	   bit.

	   For now, just do baud. */

	speed = tty_get_baud_rate(tty);
	speed = keyspan_pda_setbaud(serial, speed);

	if (speed == 0) {
		dbg("can't handle requested baud rate");
		/* It hasn't changed so.. */
		speed = tty_termios_baud_rate(old_termios);
	}
	/* Only speed can change so copy the old h/w parameters
	   then encode the new speed */
	tty_termios_copy_hw(tty->termios, old_termios);
	tty_encode_baud_rate(tty, speed, speed);
}