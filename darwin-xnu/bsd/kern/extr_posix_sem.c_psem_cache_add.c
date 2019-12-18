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
struct psemname {scalar_t__ psem_namelen; int /*<<< orphan*/  psem_nameptr; } ;
struct pseminfo {int dummy; } ;
struct psemhashhead {struct psemcache* lh_first; } ;
struct TYPE_2__ {struct psemcache* le_next; } ;
struct psemcache {scalar_t__ psem_nlen; TYPE_1__ psem_hash; int /*<<< orphan*/  psem_name; struct pseminfo* pseminfo; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOSPC ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct psemhashhead*,struct psemcache*,int /*<<< orphan*/ ) ; 
 scalar_t__ PSEMCACHE_FOUND ; 
 struct psemhashhead* PSEMHASH (struct psemname*) ; 
 scalar_t__ PSEMNAMLEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ posix_sem_max ; 
 scalar_t__ psem_cache_search (struct pseminfo**,struct psemname*,struct psemcache**) ; 
 int /*<<< orphan*/  psem_hash ; 
 scalar_t__ psemnument ; 

__attribute__((used)) static int
psem_cache_add(struct pseminfo *psemp, struct psemname *pnp, struct psemcache *pcp)
{
	struct psemhashhead *pcpp;
	struct pseminfo *dpinfo;
	struct psemcache *dpcp;

#if DIAGNOSTIC
	if (pnp->psem_namelen > PSEMNAMLEN)
		panic("cache_enter: name too long");
#endif


	/*  if the entry has already been added by some one else return */
	if (psem_cache_search(&dpinfo, pnp, &dpcp) == PSEMCACHE_FOUND) {
		return EEXIST;
	}
	if (psemnument >= posix_sem_max)
		return ENOSPC;
	psemnument++;
	/*
	 * Fill in cache info, if vp is NULL this is a "negative" cache entry.
	 * For negative entries, we have to record whether it is a whiteout.
	 * the whiteout flag is stored in the nc_vpid field which is
	 * otherwise unused.
	 */
	pcp->pseminfo = psemp;
	pcp->psem_nlen = pnp->psem_namelen;
	bcopy(pnp->psem_nameptr, pcp->psem_name, (unsigned)pcp->psem_nlen);
	pcpp = PSEMHASH(pnp);
#if DIAGNOSTIC
	{
		struct psemcache *p;

		for (p = pcpp->lh_first; p != 0; p = p->psem_hash.le_next)
			if (p == pcp)
				panic("psem:cache_enter duplicate");
	}
#endif
	LIST_INSERT_HEAD(pcpp, pcp, psem_hash);
	return 0;
}