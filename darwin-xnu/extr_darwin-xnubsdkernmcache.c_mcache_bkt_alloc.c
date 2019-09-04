#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mc_bkt_lock; int /*<<< orphan*/ * cache_bkttype; int /*<<< orphan*/  mc_bkt_contention; } ;
typedef  TYPE_1__ mcache_t ;
typedef  int /*<<< orphan*/  mcache_bkttype_t ;
struct TYPE_8__ {scalar_t__ bl_total; scalar_t__ bl_min; int /*<<< orphan*/  bl_alloc; TYPE_3__* bl_list; } ;
typedef  TYPE_2__ mcache_bktlist_t ;
struct TYPE_9__ {struct TYPE_9__* bkt_next; } ;
typedef  TYPE_3__ mcache_bkt_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCACHE_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCACHE_LOCK_TRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCACHE_UNLOCK (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mcache_bkt_t *
mcache_bkt_alloc(mcache_t *cp, mcache_bktlist_t *blp, mcache_bkttype_t **btp)
{
	mcache_bkt_t *bkt;

	if (!MCACHE_LOCK_TRY(&cp->mc_bkt_lock)) {
		/*
		 * The bucket layer lock is held by another CPU; increase
		 * the contention count so that we can later resize the
		 * bucket size accordingly.
		 */
		MCACHE_LOCK(&cp->mc_bkt_lock);
		cp->mc_bkt_contention++;
	}

	if ((bkt = blp->bl_list) != NULL) {
		blp->bl_list = bkt->bkt_next;
		if (--blp->bl_total < blp->bl_min)
			blp->bl_min = blp->bl_total;
		blp->bl_alloc++;
	}

	if (btp != NULL)
		*btp = cp->cache_bkttype;

	MCACHE_UNLOCK(&cp->mc_bkt_lock);

	return (bkt);
}