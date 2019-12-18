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
struct tty_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rxtotal; int /*<<< orphan*/  rxbreaks; int /*<<< orphan*/  rxoverrun; int /*<<< orphan*/  rxframing; int /*<<< orphan*/  rxparity; } ;
struct TYPE_4__ {int flags; } ;
struct stlport {unsigned int ioaddr; unsigned char rxignoremsk; unsigned char rxmarkmsk; TYPE_1__ stats; int /*<<< orphan*/  pagenr; int /*<<< orphan*/  brdnr; TYPE_2__ port; } ;

/* Variables and functions */
 int ASYNC_SAK ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char SR_RXBREAK ; 
 unsigned char SR_RXFRAMING ; 
 unsigned char SR_RXOVERRUN ; 
 unsigned char SR_RXPARITY ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_OVERRUN ; 
 unsigned char TTY_PARITY ; 
 int /*<<< orphan*/  do_SAK (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char,unsigned char) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_struct*) ; 

__attribute__((used)) static void stl_sc26198rxbadch(struct stlport *portp, unsigned char status, char ch)
{
	struct tty_struct	*tty;
	unsigned int		ioaddr;

	tty = tty_port_tty_get(&portp->port);
	ioaddr = portp->ioaddr;

	if (status & SR_RXPARITY)
		portp->stats.rxparity++;
	if (status & SR_RXFRAMING)
		portp->stats.rxframing++;
	if (status & SR_RXOVERRUN)
		portp->stats.rxoverrun++;
	if (status & SR_RXBREAK)
		portp->stats.rxbreaks++;

	if ((tty != NULL) &&
	    ((portp->rxignoremsk & status) == 0)) {
		if (portp->rxmarkmsk & status) {
			if (status & SR_RXBREAK) {
				status = TTY_BREAK;
				if (portp->port.flags & ASYNC_SAK) {
					do_SAK(tty);
					BRDENABLE(portp->brdnr, portp->pagenr);
				}
			} else if (status & SR_RXPARITY)
				status = TTY_PARITY;
			else if (status & SR_RXFRAMING)
				status = TTY_FRAME;
			else if(status & SR_RXOVERRUN)
				status = TTY_OVERRUN;
			else
				status = 0;
		} else
			status = 0;

		tty_insert_flip_char(tty, ch, status);
		tty_schedule_flip(tty);

		if (status == 0)
			portp->stats.rxtotal++;
	}
	tty_kref_put(tty);
}