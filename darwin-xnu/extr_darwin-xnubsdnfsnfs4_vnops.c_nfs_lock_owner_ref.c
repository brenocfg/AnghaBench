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
struct nfs_lock_owner {int /*<<< orphan*/  nlo_lock; int /*<<< orphan*/  nlo_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
nfs_lock_owner_ref(struct nfs_lock_owner *nlop)
{
	lck_mtx_lock(&nlop->nlo_lock);
	nlop->nlo_refcnt++;
	lck_mtx_unlock(&nlop->nlo_lock);
}