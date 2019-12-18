#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int flags; } ;
struct isi_port {TYPE_1__ port; struct isi_board* card; } ;
struct isi_board {scalar_t__ count; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  drop_dtr (struct isi_port*) ; 
 int /*<<< orphan*/  isicom_shutdown_board (struct isi_board*) ; 
 int /*<<< orphan*/  pr_dbg (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_free_xmit_buf (TYPE_1__*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isicom_shutdown_port(struct isi_port *port)
{
	struct isi_board *card = port->card;
	struct tty_struct *tty;

	tty = tty_port_tty_get(&port->port);

	if (!(port->port.flags & ASYNC_INITIALIZED)) {
		tty_kref_put(tty);
		return;
	}

	tty_port_free_xmit_buf(&port->port);
	port->port.flags &= ~ASYNC_INITIALIZED;
	/* 3rd October 2000 : Vinayak P Risbud */
	tty_port_tty_set(&port->port, NULL);

	/*Fix done by Anil .S on 30-04-2001
	remote login through isi port has dtr toggle problem
	due to which the carrier drops before the password prompt
	appears on the remote end. Now we drop the dtr only if the
	HUPCL(Hangup on close) flag is set for the tty*/

	if (C_HUPCL(tty))
		/* drop dtr on this port */
		drop_dtr(port);

	/* any other port uninits  */
	if (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);

	if (--card->count < 0) {
		pr_dbg("isicom_shutdown_port: bad board(0x%lx) count %d.\n",
			card->base, card->count);
		card->count = 0;
	}

	/* last port was closed, shutdown that boad too */
	if (C_HUPCL(tty)) {
		if (!card->count)
			isicom_shutdown_board(card);
	}
	tty_kref_put(tty);
}