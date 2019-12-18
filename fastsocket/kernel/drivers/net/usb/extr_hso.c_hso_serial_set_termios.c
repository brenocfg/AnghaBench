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
struct tty_struct {struct ktermios* termios; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; } ;
struct hso_serial {int /*<<< orphan*/  serial_lock; scalar_t__ open_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  D5 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hso_serial_set_termios (struct tty_struct*,struct ktermios*) ; 
 struct hso_serial* get_serial_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hso_serial_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct hso_serial *serial = get_serial_by_tty(tty);
	unsigned long flags;

	if (old)
		D5("Termios called with: cflags new[%d] - old[%d]",
		   tty->termios->c_cflag, old->c_cflag);

	/* the actual setup */
	spin_lock_irqsave(&serial->serial_lock, flags);
	if (serial->open_count)
		_hso_serial_set_termios(tty, old);
	else
		tty->termios = old;
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	/* done */
	return;
}