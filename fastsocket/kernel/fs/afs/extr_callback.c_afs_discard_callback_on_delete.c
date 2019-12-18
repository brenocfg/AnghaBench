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
struct afs_vnode {int cb_promised; int /*<<< orphan*/  cb_promise; struct afs_server* server; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rb_node; } ;
struct afs_server {int /*<<< orphan*/  cb_lock; TYPE_1__ cb_promises; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void afs_discard_callback_on_delete(struct afs_vnode *vnode)
{
	struct afs_server *server = vnode->server;

	_enter("%d", vnode->cb_promised);

	if (!vnode->cb_promised) {
		_leave(" [not promised]");
		return;
	}

	ASSERT(server != NULL);

	spin_lock(&server->cb_lock);
	if (vnode->cb_promised) {
		ASSERT(server->cb_promises.rb_node != NULL);
		rb_erase(&vnode->cb_promise, &server->cb_promises);
		vnode->cb_promised = false;
	}
	spin_unlock(&server->cb_lock);
	_leave("");
}