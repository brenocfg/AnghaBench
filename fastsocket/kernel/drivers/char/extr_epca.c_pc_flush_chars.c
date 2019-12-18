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
struct channel {int statusflags; } ;

/* Variables and functions */
 int EMPTYWAIT ; 
 int TXBUSY ; 
 int /*<<< orphan*/  epca_lock ; 
 int /*<<< orphan*/  setup_empty_event (struct tty_struct*,struct channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct channel* verifyChannel (struct tty_struct*) ; 

__attribute__((used)) static void pc_flush_chars(struct tty_struct *tty)
{
	struct channel *ch;
	/*
	 * verifyChannel returns the channel from the tty struct if it is
	 * valid. This serves as a sanity check.
	 */
	ch = verifyChannel(tty);
	if (ch != NULL) {
		unsigned long flags;
		spin_lock_irqsave(&epca_lock, flags);
		/*
		 * If not already set and the transmitter is busy setup an
		 * event to indicate when the transmit empties.
		 */
		if ((ch->statusflags & TXBUSY) &&
				!(ch->statusflags & EMPTYWAIT))
			setup_empty_event(tty, ch);
		spin_unlock_irqrestore(&epca_lock, flags);
	}
}