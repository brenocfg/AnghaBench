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
struct pshmname {scalar_t__ pshm_namelen; int /*<<< orphan*/  pshm_nameptr; } ;
struct pshminfo {int dummy; } ;
struct pshmhashhead {struct pshmcache* lh_first; } ;
struct TYPE_2__ {struct pshmcache* le_next; } ;
struct pshmcache {scalar_t__ pshm_nlen; TYPE_1__ pshm_hash; int /*<<< orphan*/  pshm_name; struct pshminfo* pshminfo; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct pshmhashhead*,struct pshmcache*,int /*<<< orphan*/ ) ; 
 scalar_t__ PSHMCACHE_FOUND ; 
 struct pshmhashhead* PSHMHASH (struct pshmname*) ; 
 scalar_t__ PSHMNAMLEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pshm_cache_search (struct pshminfo**,struct pshmname*,struct pshmcache**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pshm_hash ; 
 int /*<<< orphan*/  pshmnument ; 

__attribute__((used)) static int
pshm_cache_add(struct pshminfo *pshmp, struct pshmname *pnp, struct pshmcache *pcp)
{
	struct pshmhashhead *pcpp;
	struct pshminfo *dpinfo;
	struct pshmcache *dpcp;

#if DIAGNOSTIC
	if (pnp->pshm_namelen > PSHMNAMLEN)
		panic("cache_enter: name too long");
#endif


	/*  if the entry has already been added by some one else return */
	if (pshm_cache_search(&dpinfo, pnp, &dpcp, 0) == PSHMCACHE_FOUND) {
		return EEXIST;
	}
	pshmnument++;

	/*
	 * Fill in cache info, if vp is NULL this is a "negative" cache entry.
	 */
	pcp->pshminfo = pshmp;
	pcp->pshm_nlen = pnp->pshm_namelen;
	bcopy(pnp->pshm_nameptr, pcp->pshm_name, (unsigned)pcp->pshm_nlen);
	pcpp = PSHMHASH(pnp);
#if DIAGNOSTIC
	{
		struct pshmcache *p;

		for (p = pcpp->lh_first; p != 0; p = p->pshm_hash.le_next)
			if (p == pcp)
				panic("cache_enter: duplicate");
	}
#endif
	LIST_INSERT_HEAD(pcpp, pcp, pshm_hash);
	return 0;
}