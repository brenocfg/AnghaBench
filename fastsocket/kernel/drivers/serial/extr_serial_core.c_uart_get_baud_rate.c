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
typedef  scalar_t__ upf_t ;
struct uart_port {scalar_t__ flags; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBAUD ; 
 scalar_t__ UPF_SPD_HI ; 
 scalar_t__ UPF_SPD_MASK ; 
 scalar_t__ UPF_SPD_SHI ; 
 scalar_t__ UPF_SPD_VHI ; 
 scalar_t__ UPF_SPD_WARP ; 
 unsigned int tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,int,int) ; 

unsigned int
uart_get_baud_rate(struct uart_port *port, struct ktermios *termios,
		   struct ktermios *old, unsigned int min, unsigned int max)
{
	unsigned int try, baud, altbaud = 38400;
	int hung_up = 0;
	upf_t flags = port->flags & UPF_SPD_MASK;

	if (flags == UPF_SPD_HI)
		altbaud = 57600;
	if (flags == UPF_SPD_VHI)
		altbaud = 115200;
	if (flags == UPF_SPD_SHI)
		altbaud = 230400;
	if (flags == UPF_SPD_WARP)
		altbaud = 460800;

	for (try = 0; try < 2; try++) {
		baud = tty_termios_baud_rate(termios);

		/*
		 * The spd_hi, spd_vhi, spd_shi, spd_warp kludge...
		 * Die! Die! Die!
		 */
		if (baud == 38400)
			baud = altbaud;

		/*
		 * Special case: B0 rate.
		 */
		if (baud == 0) {
			hung_up = 1;
			baud = 9600;
		}

		if (baud >= min && baud <= max)
			return baud;

		/*
		 * Oops, the quotient was zero.  Try again with
		 * the old baud rate if possible.
		 */
		termios->c_cflag &= ~CBAUD;
		if (old) {
			baud = tty_termios_baud_rate(old);
			if (!hung_up)
				tty_termios_encode_baud_rate(termios,
								baud, baud);
			old = NULL;
			continue;
		}

		/*
		 * As a last resort, if the quotient is zero,
		 * default to 9600 bps
		 */
		if (!hung_up)
			tty_termios_encode_baud_rate(termios, 9600, 9600);
	}

	return 0;
}