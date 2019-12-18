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
struct nfs_client {int /*<<< orphan*/  cl_superblocks; int /*<<< orphan*/  cl_share_link; int /*<<< orphan*/  cl_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_cb_idr_remove_locked (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_client_lock ; 
 int /*<<< orphan*/  nfs_free_client (struct nfs_client*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_put_client(struct nfs_client *clp)
{
	if (!clp)
		return;

	dprintk("--> nfs_put_client({%d})\n", atomic_read(&clp->cl_count));

	if (atomic_dec_and_lock(&clp->cl_count, &nfs_client_lock)) {
		list_del(&clp->cl_share_link);
		nfs_cb_idr_remove_locked(clp);
		spin_unlock(&nfs_client_lock);

		BUG_ON(!list_empty(&clp->cl_superblocks));

		nfs_free_client(clp);
	}
}