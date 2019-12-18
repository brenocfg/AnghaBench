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
struct tty_port {int dummy; } ;
struct file {int dummy; } ;
struct channel {scalar_t__ event; struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  pc_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  shutdown (struct channel*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (struct tty_port*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (struct tty_port*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 
 struct channel* verifyChannel (struct tty_struct*) ; 

__attribute__((used)) static void pc_close(struct tty_struct *tty, struct file *filp)
{
	struct channel *ch;
	struct tty_port *port;
	/*
	 * verifyChannel returns the channel from the tty struct if it is
	 * valid. This serves as a sanity check.
	 */
	ch = verifyChannel(tty);
	if (ch == NULL)
		return;
	port = &ch->port;

	if (tty_port_close_start(port, tty, filp) == 0)
		return;

	pc_flush_buffer(tty);
	shutdown(ch, tty);

	tty_port_close_end(port, tty);
	ch->event = 0;	/* FIXME: review ch->event locking */
	tty_port_tty_set(port, NULL);
}