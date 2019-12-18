#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_inode {int dummy; } ;
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct nfs_client {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {struct nfs_client* nfs_client; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int nfs4_wait_clnt_recover (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_abort_delegation_return (struct nfs_delegation*,struct nfs_client*) ; 
 int nfs_delegation_claim_opens (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_detach_delegation (struct nfs_inode*,struct nfs_delegation*,TYPE_1__*) ; 
 int nfs_do_return_delegation (struct inode*,struct nfs_delegation*,int) ; 

__attribute__((used)) static int nfs_end_delegation_return(struct inode *inode, struct nfs_delegation *delegation, int issync)
{
	struct nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	struct nfs_inode *nfsi = NFS_I(inode);
	int err;

	if (delegation == NULL)
		return 0;
	do {
		err = nfs_delegation_claim_opens(inode, &delegation->stateid);
		if (!issync || err != -EAGAIN)
			break;
		/*
		 * Guard against state recovery
		 */
		err = nfs4_wait_clnt_recover(clp);
	} while (err == 0);

	if (err) {
		nfs_abort_delegation_return(delegation, clp);
		goto out;
	}
	if (!nfs_detach_delegation(nfsi, delegation, NFS_SERVER(inode)))
		goto out;

	err = nfs_do_return_delegation(inode, delegation, issync);
out:
	return err;
}