#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mc_sync_lock; int /*<<< orphan*/  mc_enable_cnt; } ;
typedef  TYPE_1__ mcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcache_bkt_purge (TYPE_1__*) ; 

__attribute__((used)) static void
mcache_purge(void *arg)
{
	mcache_t *cp = arg;

	mcache_bkt_purge(cp);
	/*
	 * We cannot simply call mcache_cache_bkt_enable() from here as
	 * a bucket resize may be in flight and we would cause the CPU
	 * layers of the cache to point to different sizes.  Therefore,
	 * we simply increment the enable count so that during the next
	 * periodic cache update the buckets can be reenabled.
	 */
	lck_mtx_lock_spin(&cp->mc_sync_lock);
	cp->mc_enable_cnt++;
	lck_mtx_unlock(&cp->mc_sync_lock);
}