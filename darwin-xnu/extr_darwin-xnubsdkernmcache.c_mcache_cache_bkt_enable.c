#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mc_flags; TYPE_1__* cache_bkttype; TYPE_3__* mc_cpu; } ;
typedef  TYPE_2__ mcache_t ;
struct TYPE_7__ {int /*<<< orphan*/  cc_lock; int /*<<< orphan*/  cc_bktsize; } ;
typedef  TYPE_3__ mcache_cpu_t ;
struct TYPE_5__ {int /*<<< orphan*/  bt_bktsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCACHE_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCACHE_UNLOCK (int /*<<< orphan*/ *) ; 
 int MCF_NOCPUCACHE ; 
 int ncpu ; 

__attribute__((used)) static void
mcache_cache_bkt_enable(mcache_t *cp)
{
	mcache_cpu_t *ccp;
	int cpu;

	if (cp->mc_flags & MCF_NOCPUCACHE)
		return;

	for (cpu = 0; cpu < ncpu; cpu++) {
		ccp = &cp->mc_cpu[cpu];
		MCACHE_LOCK(&ccp->cc_lock);
		ccp->cc_bktsize = cp->cache_bkttype->bt_bktsize;
		MCACHE_UNLOCK(&ccp->cc_lock);
	}
}