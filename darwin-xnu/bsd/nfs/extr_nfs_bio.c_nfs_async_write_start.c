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
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
struct nfsmount {scalar_t__ nm_asyncwrites; int /*<<< orphan*/  nm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 scalar_t__ NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int PCATCH ; 
 int PZERO ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 scalar_t__ nfs_max_async_writes ; 
 int nfs_sigintr (struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
nfs_async_write_start(struct nfsmount *nmp)
{
	int error = 0, slpflag = NMFLAG(nmp, INTR) ? PCATCH : 0;
	struct timespec ts = {1, 0};

	if (nfs_max_async_writes <= 0)
		return (0);
	lck_mtx_lock(&nmp->nm_lock);
	while ((nfs_max_async_writes > 0) && (nmp->nm_asyncwrites >= nfs_max_async_writes)) {
		if ((error = nfs_sigintr(nmp, NULL, current_thread(), 1)))
			break;
		msleep(&nmp->nm_asyncwrites, &nmp->nm_lock, slpflag|(PZERO-1), "nfsasyncwrites", &ts);
		slpflag = 0;
	}
	if (!error)
		nmp->nm_asyncwrites++;
	lck_mtx_unlock(&nmp->nm_lock);
	return (error);
}