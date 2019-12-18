#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct nfs_client {TYPE_1__* cl_mvops; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_6__ {int /*<<< orphan*/  delegation; } ;
struct TYPE_5__ {struct nfs_client* nfs_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* match_stateid ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_3__* NFS_I (struct inode*) ; 
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  filemap_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_delegation_run_state_manager (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_mark_return_delegation (struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int nfs_async_inode_return_delegation(struct inode *inode,
				      const nfs4_stateid *stateid)
{
	struct nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	struct nfs_delegation *delegation;

	filemap_flush(inode->i_mapping);

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);

	if (!clp->cl_mvops->match_stateid(&delegation->stateid, stateid)) {
		rcu_read_unlock();
		return -ENOENT;
	}
	nfs_mark_return_delegation(delegation);
	rcu_read_unlock();

	nfs_delegation_run_state_manager(clp);
	return 0;
}