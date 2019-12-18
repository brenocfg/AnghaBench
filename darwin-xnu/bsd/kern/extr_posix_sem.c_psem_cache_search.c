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
struct psemname {scalar_t__ psem_namelen; int /*<<< orphan*/  psem_nameptr; } ;
struct pseminfo {int dummy; } ;
struct psemhashhead {struct psemcache* lh_first; } ;
struct TYPE_3__ {struct psemcache* le_next; } ;
struct psemcache {scalar_t__ psem_nlen; struct pseminfo* pseminfo; int /*<<< orphan*/  psem_name; TYPE_1__ psem_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  neghits; int /*<<< orphan*/  goodhits; int /*<<< orphan*/  miss; int /*<<< orphan*/  longnames; } ;

/* Variables and functions */
 int PSEMCACHE_FOUND ; 
 int PSEMCACHE_NEGATIVE ; 
 int PSEMCACHE_NOTFOUND ; 
 struct psemhashhead* PSEMHASH (struct psemname*) ; 
 scalar_t__ PSEMNAMLEN ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ psemstats ; 

__attribute__((used)) static int
psem_cache_search(struct pseminfo **psemp, struct psemname *pnp,
		  struct psemcache **pcache)
{
	struct psemcache *pcp, *nnp;
	struct psemhashhead *pcpp;

	if (pnp->psem_namelen > PSEMNAMLEN) {
		psemstats.longnames++;
		return PSEMCACHE_NOTFOUND;
	}

	pcpp = PSEMHASH(pnp);
	for (pcp = pcpp->lh_first; pcp != 0; pcp = nnp) {
		nnp = pcp->psem_hash.le_next;
		if (pcp->psem_nlen == pnp->psem_namelen &&
		    !bcmp(pcp->psem_name, pnp->psem_nameptr, 						(u_int)pcp-> psem_nlen))
			break;
	}

	if (pcp == 0) {
		psemstats.miss++;
		return PSEMCACHE_NOTFOUND;
	}

	/* We found a "positive" match, return the vnode */
        if (pcp->pseminfo) {
		psemstats.goodhits++;
		/* TOUCH(ncp); */
		*psemp = pcp->pseminfo;
		*pcache = pcp;
		return PSEMCACHE_FOUND;
	}

	/*
	 * We found a "negative" match, ENOENT notifies client of this match.
	 * The nc_vpid field records whether this is a whiteout.
	 */
	psemstats.neghits++;
	return PSEMCACHE_NEGATIVE;
}