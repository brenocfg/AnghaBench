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
struct afs_vnode {scalar_t__ cb_promised; int /*<<< orphan*/  vfs_inode; struct afs_server* server; } ;
struct afs_server {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  cb_break_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ afs_breakring_space (struct afs_server*) ; 
 int /*<<< orphan*/  afs_do_give_up_callback (struct afs_server*,struct afs_vnode*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  myself ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void afs_give_up_callback(struct afs_vnode *vnode)
{
	struct afs_server *server = vnode->server;

	DECLARE_WAITQUEUE(myself, current);

	_enter("%d", vnode->cb_promised);

	_debug("GIVE UP INODE %p", &vnode->vfs_inode);

	if (!vnode->cb_promised) {
		_leave(" [not promised]");
		return;
	}

	ASSERT(server != NULL);

	spin_lock(&server->cb_lock);
	if (vnode->cb_promised && afs_breakring_space(server) == 0) {
		add_wait_queue(&server->cb_break_waitq, &myself);
		for (;;) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			if (!vnode->cb_promised ||
			    afs_breakring_space(server) != 0)
				break;
			spin_unlock(&server->cb_lock);
			schedule();
			spin_lock(&server->cb_lock);
		}
		remove_wait_queue(&server->cb_break_waitq, &myself);
		__set_current_state(TASK_RUNNING);
	}

	/* of course, it's always possible for the server to break this vnode's
	 * callback first... */
	if (vnode->cb_promised)
		afs_do_give_up_callback(server, vnode);

	spin_unlock(&server->cb_lock);
	_leave("");
}