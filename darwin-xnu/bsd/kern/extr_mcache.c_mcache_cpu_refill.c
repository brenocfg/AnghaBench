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
struct TYPE_3__ {int cc_objs; int cc_bktsize; int cc_pobjs; int /*<<< orphan*/ * cc_filled; int /*<<< orphan*/ * cc_pfilled; } ;
typedef  TYPE_1__ mcache_cpu_t ;
typedef  int /*<<< orphan*/  mcache_bkt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static void
mcache_cpu_refill(mcache_cpu_t *ccp, mcache_bkt_t *bkt, int objs)
{
	ASSERT((ccp->cc_filled == NULL && ccp->cc_objs == -1) ||
	    (ccp->cc_filled && ccp->cc_objs + objs == ccp->cc_bktsize));
	ASSERT(ccp->cc_bktsize > 0);

	ccp->cc_pfilled = ccp->cc_filled;
	ccp->cc_pobjs = ccp->cc_objs;
	ccp->cc_filled = bkt;
	ccp->cc_objs = objs;
}