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
struct nfs_delegation {int /*<<< orphan*/  stateid; int /*<<< orphan*/  cred; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int nfs4_proc_delegreturn (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs_free_delegation (struct nfs_delegation*) ; 

__attribute__((used)) static int nfs_do_return_delegation(struct inode *inode, struct nfs_delegation *delegation, int issync)
{
	int res = 0;

	res = nfs4_proc_delegreturn(inode, delegation->cred, &delegation->stateid, issync);
	nfs_free_delegation(delegation);
	return res;
}