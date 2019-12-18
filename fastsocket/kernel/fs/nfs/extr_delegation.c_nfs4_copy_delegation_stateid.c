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
struct nfs_inode {int /*<<< orphan*/  delegation; } ;
struct nfs_delegation {int type; int /*<<< orphan*/  stateid; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mark_delegation_referenced (struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool nfs4_copy_delegation_stateid(nfs4_stateid *dst, struct inode *inode,
		fmode_t flags)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_delegation *delegation;
	bool ret;

	flags &= FMODE_READ|FMODE_WRITE;
	rcu_read_lock();
	delegation = rcu_dereference(nfsi->delegation);
	ret = (delegation != NULL && (delegation->type & flags) == flags);
	if (ret) {
		nfs4_stateid_copy(dst, &delegation->stateid);
		nfs_mark_delegation_referenced(delegation);
	}
	rcu_read_unlock();
	return ret;
}