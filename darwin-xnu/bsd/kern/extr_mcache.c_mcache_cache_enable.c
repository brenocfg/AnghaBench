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
struct TYPE_3__ {int /*<<< orphan*/  mc_sync_lock; scalar_t__ mc_enable_cnt; scalar_t__ mc_purge_cnt; } ;
typedef  TYPE_1__ mcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcache_cache_bkt_enable (TYPE_1__*) ; 

__attribute__((used)) static void
mcache_cache_enable(void *arg)
{
	mcache_t *cp = arg;

	lck_mtx_lock_spin(&cp->mc_sync_lock);
	cp->mc_purge_cnt = 0;
	cp->mc_enable_cnt = 0;
	lck_mtx_unlock(&cp->mc_sync_lock);

	mcache_cache_bkt_enable(cp);
}