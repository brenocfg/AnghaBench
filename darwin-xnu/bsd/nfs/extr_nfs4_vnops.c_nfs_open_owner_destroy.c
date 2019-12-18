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
struct nfs_open_owner {int /*<<< orphan*/  noo_lock; scalar_t__ noo_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct nfs_open_owner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  kauth_cred_unref (scalar_t__*) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_grp ; 

void
nfs_open_owner_destroy(struct nfs_open_owner *noop)
{
	if (noop->noo_cred)
		kauth_cred_unref(&noop->noo_cred);
	lck_mtx_destroy(&noop->noo_lock, nfs_open_grp);
	FREE(noop, M_TEMP);
}