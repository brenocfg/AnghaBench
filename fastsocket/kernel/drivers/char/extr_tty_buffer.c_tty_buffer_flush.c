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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct tty_struct {TYPE_1__ buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  read_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_FLUSHING ; 
 int /*<<< orphan*/  TTY_FLUSHPENDING ; 
 int /*<<< orphan*/  __tty_buffer_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void tty_buffer_flush(struct tty_struct *tty)
{
	unsigned long flags;
	spin_lock_irqsave(&tty->buf.lock, flags);

	/* If the data is being pushed to the tty layer then we can't
	   process it here. Instead set a flag and the flush_to_ldisc
	   path will process the flush request before it exits */
	if (test_bit(TTY_FLUSHING, &tty->flags)) {
		set_bit(TTY_FLUSHPENDING, &tty->flags);
		spin_unlock_irqrestore(&tty->buf.lock, flags);
		wait_event(tty->read_wait,
				test_bit(TTY_FLUSHPENDING, &tty->flags) == 0);
		return;
	} else
		__tty_buffer_flush(tty);
	spin_unlock_irqrestore(&tty->buf.lock, flags);
}