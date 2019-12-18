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
struct rpc_cred {int dummy; } ;
struct nfs_openres {int /*<<< orphan*/  maxsize; int /*<<< orphan*/  delegation_type; int /*<<< orphan*/  delegation; } ;
struct nfs_delegation {int /*<<< orphan*/  lock; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; struct rpc_cred* cred; int /*<<< orphan*/  maxsize; int /*<<< orphan*/  stateid; int /*<<< orphan*/ * inode; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  delegation_state; int /*<<< orphan*/  delegation; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATION_NEED_RECLAIM ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rpc_cred* get_rpccred (struct rpc_cred*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_inode_set_delegation (struct inode*,struct rpc_cred*,struct nfs_openres*) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_inode_reclaim_delegation(struct inode *inode, struct rpc_cred *cred,
				  struct nfs_openres *res)
{
	struct nfs_delegation *delegation;
	struct rpc_cred *oldcred = NULL;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation != NULL) {
		spin_lock(&delegation->lock);
		if (delegation->inode != NULL) {
			nfs4_stateid_copy(&delegation->stateid, &res->delegation);
			delegation->type = res->delegation_type;
			delegation->maxsize = res->maxsize;
			oldcred = delegation->cred;
			delegation->cred = get_rpccred(cred);
			clear_bit(NFS_DELEGATION_NEED_RECLAIM,
				  &delegation->flags);
			NFS_I(inode)->delegation_state = delegation->type;
			spin_unlock(&delegation->lock);
			put_rpccred(oldcred);
			rcu_read_unlock();
		} else {
			/* We appear to have raced with a delegation return. */
			spin_unlock(&delegation->lock);
			rcu_read_unlock();
			nfs_inode_set_delegation(inode, cred, res);
		}
	} else {
		rcu_read_unlock();
	}
}