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
struct cardstate {int /*<<< orphan*/  lock; struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ANY ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,unsigned char*,size_t) ; 

void gigaset_if_receive(struct cardstate *cs,
			unsigned char *buffer, size_t len)
{
	unsigned long flags;
	struct tty_struct *tty;

	spin_lock_irqsave(&cs->lock, flags);
	if ((tty = cs->tty) == NULL)
		gig_dbg(DEBUG_ANY, "receive on closed device");
	else {
		tty_insert_flip_string(tty, buffer, len);
		tty_flip_buffer_push(tty);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
}