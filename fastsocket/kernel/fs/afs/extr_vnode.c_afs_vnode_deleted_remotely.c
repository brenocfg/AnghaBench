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
struct afs_vnode {int cb_promised; struct afs_server* server; int /*<<< orphan*/  server_rb; int /*<<< orphan*/  cb_promise; int /*<<< orphan*/  flags; } ;
struct afs_server {int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  fs_vnodes; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  cb_promises; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  _enter (char*,struct afs_server*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_put_server (struct afs_server*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_vnode_deleted_remotely(struct afs_vnode *vnode)
{
	struct afs_server *server;

	_enter("{%p}", vnode->server);

	set_bit(AFS_VNODE_DELETED, &vnode->flags);

	server = vnode->server;
	if (server) {
		if (vnode->cb_promised) {
			spin_lock(&server->cb_lock);
			if (vnode->cb_promised) {
				rb_erase(&vnode->cb_promise,
					 &server->cb_promises);
				vnode->cb_promised = false;
			}
			spin_unlock(&server->cb_lock);
		}

		spin_lock(&server->fs_lock);
		rb_erase(&vnode->server_rb, &server->fs_vnodes);
		spin_unlock(&server->fs_lock);

		vnode->server = NULL;
		afs_put_server(server);
	} else {
		ASSERT(!vnode->cb_promised);
	}

	_leave("");
}