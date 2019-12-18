#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int node; int /*<<< orphan*/ * key; } ;
struct TYPE_7__ {size_t handle; } ;
struct TYPE_6__ {size_t size; int freeList; TYPE_3__* handles; TYPE_2__* nodes; } ;
typedef  TYPE_1__ PriorityQHeap ;
typedef  TYPE_2__ PQnode ;
typedef  int /*<<< orphan*/ * PQkey ;
typedef  TYPE_3__ PQhandleElem ;
typedef  size_t PQhandle ;

/* Variables and functions */
 int /*<<< orphan*/  FloatDown (TYPE_1__*,int) ; 

PQkey pqHeapExtractMin( PriorityQHeap *pq )
{
	PQnode *n = pq->nodes;
	PQhandleElem *h = pq->handles;
	PQhandle hMin = n[1].handle;
	PQkey min = h[hMin].key;

	if( pq->size > 0 ) {
		n[1].handle = n[pq->size].handle;
		h[n[1].handle].node = 1;

		h[hMin].key = NULL;
		h[hMin].node = pq->freeList;
		pq->freeList = hMin;

		if( -- pq->size > 0 ) {
			FloatDown( pq, 1 );
		}
	}
	return min;
}