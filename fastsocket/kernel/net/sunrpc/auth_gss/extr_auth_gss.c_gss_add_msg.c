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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct rpc_inode {int /*<<< orphan*/  in_downcall; struct inode vfs_inode; } ;
struct gss_upcall_msg {int /*<<< orphan*/  list; int /*<<< orphan*/  count; int /*<<< orphan*/  uid; struct rpc_inode* inode; } ;

/* Variables and functions */
 struct gss_upcall_msg* __gss_find_upcall (struct rpc_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct gss_upcall_msg *
gss_add_msg(struct gss_upcall_msg *gss_msg)
{
	struct rpc_inode *rpci = gss_msg->inode;
	struct inode *inode = &rpci->vfs_inode;
	struct gss_upcall_msg *old;

	spin_lock(&inode->i_lock);
	old = __gss_find_upcall(rpci, gss_msg->uid);
	if (old == NULL) {
		atomic_inc(&gss_msg->count);
		list_add(&gss_msg->list, &rpci->in_downcall);
	} else
		gss_msg = old;
	spin_unlock(&inode->i_lock);
	return gss_msg;
}