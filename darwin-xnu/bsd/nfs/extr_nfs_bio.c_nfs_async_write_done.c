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
struct nfsmount {scalar_t__ nm_asyncwrites; int /*<<< orphan*/  nm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_max_async_writes ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
nfs_async_write_done(struct nfsmount *nmp)
{
	if (nmp->nm_asyncwrites <= 0)
		return;
	lck_mtx_lock(&nmp->nm_lock);
	if (nmp->nm_asyncwrites-- >= nfs_max_async_writes)
		wakeup(&nmp->nm_asyncwrites);
	lck_mtx_unlock(&nmp->nm_lock);
}