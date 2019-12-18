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
struct nfs_inode {int /*<<< orphan*/  delegation; scalar_t__ delegation_state; } ;
struct nfs_delegation {int /*<<< orphan*/  lock; int /*<<< orphan*/ * inode; int /*<<< orphan*/  super_list; int /*<<< orphan*/  flags; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATION_RETURNING ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfs_delegation* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_delegation *
nfs_detach_delegation_locked(struct nfs_inode *nfsi,
		struct nfs_delegation *delegation,
		struct nfs_client *clp)
{
	struct nfs_delegation *deleg_cur =
		rcu_dereference_protected(nfsi->delegation,
				lockdep_is_held(&clp->cl_lock));

	if (deleg_cur == NULL || delegation != deleg_cur)
		return NULL;

	spin_lock(&delegation->lock);
	set_bit(NFS_DELEGATION_RETURNING, &delegation->flags);
	list_del_rcu(&delegation->super_list);
	delegation->inode = NULL;
	nfsi->delegation_state = 0;
	rcu_assign_pointer(nfsi->delegation, NULL);
	spin_unlock(&delegation->lock);
	return delegation;
}