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
struct TYPE_9__ {int node; int /*<<< orphan*/ * key; } ;
struct TYPE_8__ {size_t handle; } ;
struct TYPE_7__ {int max; size_t size; int freeList; TYPE_3__* handles; TYPE_2__* nodes; } ;
typedef  TYPE_1__ PriorityQHeap ;
typedef  TYPE_2__ PQnode ;
typedef  TYPE_3__ PQhandleElem ;
typedef  int PQhandle ;

/* Variables and functions */
 int /*<<< orphan*/  FloatDown (TYPE_1__*,int) ; 
 int /*<<< orphan*/  FloatUp (TYPE_1__*,int) ; 
 scalar_t__ LEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

void pqHeapDelete( PriorityQHeap *pq, PQhandle hCurr )
{
	PQnode *n = pq->nodes;
	PQhandleElem *h = pq->handles;
	int curr;

	assert( hCurr >= 1 && hCurr <= pq->max && h[hCurr].key != NULL );

	curr = h[hCurr].node;
	n[curr].handle = n[pq->size].handle;
	h[n[curr].handle].node = curr;

	if( curr <= -- pq->size ) {
		if( curr <= 1 || LEQ( h[n[curr>>1].handle].key, h[n[curr].handle].key )) {
			FloatDown( pq, curr );
		} else {
			FloatUp( pq, curr );
		}
	}
	h[hCurr].key = NULL;
	h[hCurr].node = pq->freeList;
	pq->freeList = hCurr;
}