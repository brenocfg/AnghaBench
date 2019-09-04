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
struct TYPE_5__ {scalar_t__ mltr_allocs; int mltr_depth; int /*<<< orphan*/ * mltr_addr; int /*<<< orphan*/  mltr_hitcount; int /*<<< orphan*/  mltr_collisions; } ;
typedef  TYPE_1__ mleak_trace_stat_t ;
struct TYPE_7__ {int ml_isaddr64; int ml_cnt; TYPE_1__* ml_trace; } ;
struct TYPE_6__ {scalar_t__ allocs; int depth; int /*<<< orphan*/ * addr; int /*<<< orphan*/  hitcount; int /*<<< orphan*/  collisions; } ;

/* Variables and functions */
 int MLEAK_NUM_TRACES ; 
 int MLEAK_STACK_DEPTH ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mleak_sort_traces () ; 
 TYPE_3__* mleak_stat ; 
 TYPE_2__** mleak_top_trace ; 

__attribute__((used)) static void
mleak_update_stats()
{
	mleak_trace_stat_t *mltr;
	int i;

	VERIFY(mleak_stat != NULL);
#ifdef __LP64__
	VERIFY(mleak_stat->ml_isaddr64);
#else
	VERIFY(!mleak_stat->ml_isaddr64);
#endif /* !__LP64__ */
	VERIFY(mleak_stat->ml_cnt == MLEAK_NUM_TRACES);

	mleak_sort_traces();

	mltr = &mleak_stat->ml_trace[0];
	bzero(mltr, sizeof (*mltr) * MLEAK_NUM_TRACES);
	for (i = 0; i < MLEAK_NUM_TRACES; i++) {
		int j;

		if (mleak_top_trace[i] == NULL ||
		    mleak_top_trace[i]->allocs == 0)
			continue;

		mltr->mltr_collisions	= mleak_top_trace[i]->collisions;
		mltr->mltr_hitcount	= mleak_top_trace[i]->hitcount;
		mltr->mltr_allocs	= mleak_top_trace[i]->allocs;
		mltr->mltr_depth	= mleak_top_trace[i]->depth;

		VERIFY(mltr->mltr_depth <= MLEAK_STACK_DEPTH);
		for (j = 0; j < mltr->mltr_depth; j++)
			mltr->mltr_addr[j] = mleak_top_trace[i]->addr[j];

		mltr++;
	}
}