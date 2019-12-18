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
struct adbdev_state {int inuse; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/ * completed; int /*<<< orphan*/  n_pending; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * adb_controller ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct adbdev_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int adb_open(struct inode *inode, struct file *file)
{
	struct adbdev_state *state;
	int ret = 0;

	lock_kernel();
	if (iminor(inode) > 0 || adb_controller == NULL) {
		ret = -ENXIO;
		goto out;
	}
	state = kmalloc(sizeof(struct adbdev_state), GFP_KERNEL);
	if (state == 0) {
		ret = -ENOMEM;
		goto out;
	}
	file->private_data = state;
	spin_lock_init(&state->lock);
	atomic_set(&state->n_pending, 0);
	state->completed = NULL;
	init_waitqueue_head(&state->wait_queue);
	state->inuse = 1;

out:
	unlock_kernel();
	return ret;
}