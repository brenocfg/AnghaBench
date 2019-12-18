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
struct tty_struct {struct moxa_port* driver_data; } ;
struct moxa_port {int statusflags; } ;

/* Variables and functions */
 int EMPTYWAIT ; 
 int MoxaPortTxQueue (struct moxa_port*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  moxa_setup_empty_event (struct tty_struct*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int moxa_chars_in_buffer(struct tty_struct *tty)
{
	struct moxa_port *ch = tty->driver_data;
	int chars;

	/*
	 * Sigh...I have to check if driver_data is NULL here, because
	 * if an open() fails, the TTY subsystem eventually calls
	 * tty_wait_until_sent(), which calls the driver's chars_in_buffer()
	 * routine.  And since the open() failed, we return 0 here.  TDJ
	 */
	if (ch == NULL)
		return 0;
	lock_kernel();
	chars = MoxaPortTxQueue(ch);
	if (chars) {
		/*
		 * Make it possible to wakeup anything waiting for output
		 * in tty_ioctl.c, etc.
		 */
		if (!(ch->statusflags & EMPTYWAIT))
			moxa_setup_empty_event(tty);
	}
	unlock_kernel();
	return chars;
}