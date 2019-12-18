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
struct afs_vnode {int cb_promised; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_locks; int /*<<< orphan*/  granted_locks; int /*<<< orphan*/  cb_broken_work; int /*<<< orphan*/  cb_promise; int /*<<< orphan*/  flags; } ;
struct afs_server {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  cb_promises; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_BROKEN ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_callback_update_worker ; 
 int /*<<< orphan*/  afs_lock_may_be_available (struct afs_vnode*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_break_callback(struct afs_server *server,
			       struct afs_vnode *vnode)
{
	_enter("");

	set_bit(AFS_VNODE_CB_BROKEN, &vnode->flags);

	if (vnode->cb_promised) {
		spin_lock(&vnode->lock);

		_debug("break callback");

		spin_lock(&server->cb_lock);
		if (vnode->cb_promised) {
			rb_erase(&vnode->cb_promise, &server->cb_promises);
			vnode->cb_promised = false;
		}
		spin_unlock(&server->cb_lock);

		queue_work(afs_callback_update_worker, &vnode->cb_broken_work);
		if (list_empty(&vnode->granted_locks) &&
		    !list_empty(&vnode->pending_locks))
			afs_lock_may_be_available(vnode);
		spin_unlock(&vnode->lock);
	}
}