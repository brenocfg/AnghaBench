#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mc_bkt_lock; scalar_t__ mc_bkt_contention; scalar_t__ mc_bkt_contention_prev; TYPE_2__* cache_bkttype; scalar_t__ mc_chunksize; } ;
typedef  TYPE_1__ mcache_t ;
struct TYPE_6__ {unsigned int bt_maxbuf; } ;
typedef  TYPE_2__ mcache_bkttype_t ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  MCACHE_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCACHE_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcache_bkt_purge (TYPE_1__*) ; 
 int /*<<< orphan*/  mcache_cache_enable (TYPE_1__*) ; 

__attribute__((used)) static void
mcache_cache_bkt_resize(void *arg)
{
	mcache_t *cp = arg;
	mcache_bkttype_t *btp = cp->cache_bkttype;

	if ((unsigned int)cp->mc_chunksize < btp->bt_maxbuf) {
		mcache_bkt_purge(cp);

		/*
		 * Upgrade to the next bucket type with larger bucket size;
		 * temporarily set the previous contention snapshot to a
		 * negative number to prevent unnecessary resize request.
		 */
		MCACHE_LOCK(&cp->mc_bkt_lock);
		cp->cache_bkttype = ++btp;
		cp ->mc_bkt_contention_prev = cp->mc_bkt_contention + INT_MAX;
		MCACHE_UNLOCK(&cp->mc_bkt_lock);

		mcache_cache_enable(cp);
	}
}