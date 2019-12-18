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
struct inode {int dummy; } ;
struct file {struct adbdev_state* private_data; } ;
struct adbdev_state {int /*<<< orphan*/  lock; scalar_t__ inuse; int /*<<< orphan*/ * completed; int /*<<< orphan*/  n_pending; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adbdev_state*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int adb_release(struct inode *inode, struct file *file)
{
	struct adbdev_state *state = file->private_data;
	unsigned long flags;

	lock_kernel();
	if (state) {
		file->private_data = NULL;
		spin_lock_irqsave(&state->lock, flags);
		if (atomic_read(&state->n_pending) == 0
		    && state->completed == NULL) {
			spin_unlock_irqrestore(&state->lock, flags);
			kfree(state);
		} else {
			state->inuse = 0;
			spin_unlock_irqrestore(&state->lock, flags);
		}
	}
	unlock_kernel();
	return 0;
}