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
struct floppy_state {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  wanted; int /*<<< orphan*/  wait; } ;
typedef  enum swim_state { ____Placeholder_swim_state } swim_state ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ available ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ idle ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grab_drive(struct floppy_state *fs, enum swim_state state,
		      int interruptible)
{
	unsigned long flags;

	spin_lock_irqsave(&fs->lock, flags);
	if (fs->state != idle) {
		++fs->wanted;
		while (fs->state != available) {
			if (interruptible && signal_pending(current)) {
				--fs->wanted;
				spin_unlock_irqrestore(&fs->lock, flags);
				return -EINTR;
			}
			interruptible_sleep_on(&fs->wait);
		}
		--fs->wanted;
	}
	fs->state = state;
	spin_unlock_irqrestore(&fs->lock, flags);
	return 0;
}