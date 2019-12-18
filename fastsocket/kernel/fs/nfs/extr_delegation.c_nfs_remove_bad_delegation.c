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
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_free_delegation (struct nfs_delegation*) ; 
 struct nfs_delegation* nfs_inode_detach_delegation (struct inode*) ; 
 int /*<<< orphan*/  nfs_inode_find_state_and_recover (struct inode*,int /*<<< orphan*/ *) ; 

void nfs_remove_bad_delegation(struct inode *inode)
{
	struct nfs_delegation *delegation;

	delegation = nfs_inode_detach_delegation(inode);
	if (delegation) {
		nfs_inode_find_state_and_recover(inode, &delegation->stateid);
		nfs_free_delegation(delegation);
	}
}