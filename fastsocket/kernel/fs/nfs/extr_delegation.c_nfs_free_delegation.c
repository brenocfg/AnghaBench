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
struct nfs_delegation {int /*<<< orphan*/  rcu; int /*<<< orphan*/ * cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_free_delegation_callback ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_free_delegation(struct nfs_delegation *delegation)
{
	if (delegation->cred) {
		put_rpccred(delegation->cred);
		delegation->cred = NULL;
	}
	call_rcu(&delegation->rcu, nfs_free_delegation_callback);
}