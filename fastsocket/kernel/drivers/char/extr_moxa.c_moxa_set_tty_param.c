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
struct tty_struct {struct moxa_port* driver_data; struct ktermios* termios; } ;
struct moxa_port {int dummy; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int CMSPAR ; 
 int CRTSCTS ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  MoxaPortFlowCtrl (struct moxa_port*,int,int,int,int,int) ; 
 int MoxaPortSetTermio (struct moxa_port*,struct ktermios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int,int) ; 
 int /*<<< orphan*/  tty_get_baud_rate (struct tty_struct*) ; 
 int tty_termios_baud_rate (struct ktermios*) ; 

__attribute__((used)) static void moxa_set_tty_param(struct tty_struct *tty, struct ktermios *old_termios)
{
	register struct ktermios *ts = tty->termios;
	struct moxa_port *ch = tty->driver_data;
	int rts, cts, txflow, rxflow, xany, baud;

	rts = cts = txflow = rxflow = xany = 0;
	if (ts->c_cflag & CRTSCTS)
		rts = cts = 1;
	if (ts->c_iflag & IXON)
		txflow = 1;
	if (ts->c_iflag & IXOFF)
		rxflow = 1;
	if (ts->c_iflag & IXANY)
		xany = 1;

	/* Clear the features we don't support */
	ts->c_cflag &= ~CMSPAR;
	MoxaPortFlowCtrl(ch, rts, cts, txflow, rxflow, xany);
	baud = MoxaPortSetTermio(ch, ts, tty_get_baud_rate(tty));
	if (baud == -1)
		baud = tty_termios_baud_rate(old_termios);
	/* Not put the baud rate into the termios data */
	tty_encode_baud_rate(tty, baud, baud);
}