#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct pshmname {scalar_t__ pshm_namelen; int /*<<< orphan*/  pshm_nameptr; } ;
struct pshminfo {int /*<<< orphan*/  pshm_usecount; } ;
struct pshmhashhead {struct pshmcache* lh_first; } ;
struct TYPE_3__ {struct pshmcache* le_next; } ;
struct pshmcache {scalar_t__ pshm_nlen; struct pshminfo* pshminfo; int /*<<< orphan*/  pshm_name; TYPE_1__ pshm_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  neghits; int /*<<< orphan*/  goodhits; int /*<<< orphan*/  miss; int /*<<< orphan*/  longnames; } ;

/* Variables and functions */
 int PSHMCACHE_FOUND ; 
 int PSHMCACHE_NEGATIVE ; 
 int PSHMCACHE_NOTFOUND ; 
 struct pshmhashhead* PSHMHASH (struct pshmname*) ; 
 scalar_t__ PSHMNAMLEN ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ pshmstats ; 

__attribute__((used)) static int
pshm_cache_search(struct pshminfo **pshmp, struct pshmname *pnp,
	struct pshmcache **pcache, int addref)
{
	struct pshmcache *pcp, *nnp;
	struct pshmhashhead *pcpp;

	if (pnp->pshm_namelen > PSHMNAMLEN) {
		pshmstats.longnames++;
		return PSHMCACHE_NOTFOUND;
	}

	pcpp = PSHMHASH(pnp);
	for (pcp = pcpp->lh_first; pcp != 0; pcp = nnp) {
		nnp = pcp->pshm_hash.le_next;
		if (pcp->pshm_nlen == pnp->pshm_namelen &&
		    !bcmp(pcp->pshm_name, pnp->pshm_nameptr, 						(u_int)pcp-> pshm_nlen))
			break;
	}

	if (pcp == 0) {
		pshmstats.miss++;
		return PSHMCACHE_NOTFOUND;
	}

	/* We found a "positive" match, return the vnode */
        if (pcp->pshminfo) {
		pshmstats.goodhits++;
		/* TOUCH(ncp); */
		*pshmp = pcp->pshminfo;
		*pcache = pcp;
		if (addref)
			pcp->pshminfo->pshm_usecount++;
		return PSHMCACHE_FOUND;
	}

	/*
	 * We found a "negative" match, ENOENT notifies client of this match.
	 */
	pshmstats.neghits++;
	return PSHMCACHE_NEGATIVE;
}