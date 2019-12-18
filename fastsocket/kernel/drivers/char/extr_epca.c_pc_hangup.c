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
struct tty_struct {int dummy; } ;
struct channel {int /*<<< orphan*/  port; scalar_t__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  pc_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  shutdown (struct channel*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 
 struct channel* verifyChannel (struct tty_struct*) ; 

__attribute__((used)) static void pc_hangup(struct tty_struct *tty)
{
	struct channel *ch;

	/*
	 * verifyChannel returns the channel from the tty struct if it is
	 * valid. This serves as a sanity check.
	 */
	ch = verifyChannel(tty);
	if (ch != NULL) {
		pc_flush_buffer(tty);
		tty_ldisc_flush(tty);
		shutdown(ch, tty);

		ch->event = 0;	/* FIXME: review locking of ch->event */
		tty_port_hangup(&ch->port);
	}
}