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
struct nfs_delegation {int type; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
typedef  int fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  delegation; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  NFS_DELEGATION_RETURNING ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  nfs_mark_delegation_referenced (struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfs_have_delegation(struct inode *inode, fmode_t flags)
{
	struct nfs_delegation *delegation;
	int ret = 0;

	flags &= FMODE_READ|FMODE_WRITE;
	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation != NULL && (delegation->type & flags) == flags &&
	    !test_bit(NFS_DELEGATION_RETURNING, &delegation->flags)) {
		nfs_mark_delegation_referenced(delegation);
		ret = 1;
	}
	rcu_read_unlock();
	return ret;
}