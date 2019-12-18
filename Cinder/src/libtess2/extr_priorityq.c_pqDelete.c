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
struct TYPE_3__ {int max; int size; int /*<<< orphan*/ *** order; int /*<<< orphan*/ ** keys; int /*<<< orphan*/  heap; } ;
typedef  TYPE_1__ PriorityQ ;
typedef  int PQhandle ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pqHeapDelete (int /*<<< orphan*/ ,int) ; 

void pqDelete( PriorityQ *pq, PQhandle curr )
{
	if( curr >= 0 ) {
		pqHeapDelete( pq->heap, curr );
		return;
	}
	curr = -(curr+1);
	assert( curr < pq->max && pq->keys[curr] != NULL );

	pq->keys[curr] = NULL;
	while( pq->size > 0 && *(pq->order[pq->size-1]) == NULL ) {
		-- pq->size;
	}
}