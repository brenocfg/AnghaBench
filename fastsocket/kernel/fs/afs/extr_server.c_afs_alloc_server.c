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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct afs_server {int /*<<< orphan*/  usage; TYPE_1__ addr; int /*<<< orphan*/  cb_break_work; int /*<<< orphan*/  cb_break_waitq; int /*<<< orphan*/  cb_lock; void* cb_promises; void* fs_vnodes; int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  sem; int /*<<< orphan*/  grave; int /*<<< orphan*/  link; struct afs_cell* cell; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct afs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_dispatch_give_up_callbacks ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct afs_server* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct in_addr const*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct afs_server *afs_alloc_server(struct afs_cell *cell,
					   const struct in_addr *addr)
{
	struct afs_server *server;

	_enter("");

	server = kzalloc(sizeof(struct afs_server), GFP_KERNEL);
	if (server) {
		atomic_set(&server->usage, 1);
		server->cell = cell;

		INIT_LIST_HEAD(&server->link);
		INIT_LIST_HEAD(&server->grave);
		init_rwsem(&server->sem);
		spin_lock_init(&server->fs_lock);
		server->fs_vnodes = RB_ROOT;
		server->cb_promises = RB_ROOT;
		spin_lock_init(&server->cb_lock);
		init_waitqueue_head(&server->cb_break_waitq);
		INIT_DELAYED_WORK(&server->cb_break_work,
				  afs_dispatch_give_up_callbacks);

		memcpy(&server->addr, addr, sizeof(struct in_addr));
		server->addr.s_addr = addr->s_addr;
	}

	_leave(" = %p{%d}", server, atomic_read(&server->usage));
	return server;
}