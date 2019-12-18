#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t node; size_t handle; int /*<<< orphan*/  key; } ;
struct TYPE_11__ {int size; int max; size_t freeList; scalar_t__ initialized; TYPE_3__* handles; TYPE_3__* nodes; } ;
struct TYPE_10__ {int /*<<< orphan*/  userData; scalar_t__ (* memrealloc ) (int /*<<< orphan*/ ,TYPE_3__*,size_t) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  TYPE_2__ PriorityQHeap ;
typedef  TYPE_3__ PQnode ;
typedef  int /*<<< orphan*/  PQkey ;
typedef  TYPE_3__ PQhandleElem ;
typedef  size_t PQhandle ;

/* Variables and functions */
 int /*<<< orphan*/  FloatUp (TYPE_2__*,int) ; 
 size_t INV_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_3__*,size_t) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_3__*,size_t) ; 

PQhandle pqHeapInsert( TESSalloc* alloc, PriorityQHeap *pq, PQkey keyNew )
{
	int curr;
	PQhandle free;

	curr = ++ pq->size;
	if( (curr*2) > pq->max ) {
		if (!alloc->memrealloc)
		{
			return INV_HANDLE;
		}
		else
		{
			PQnode *saveNodes= pq->nodes;
			PQhandleElem *saveHandles= pq->handles;

			// If the heap overflows, double its size.
			pq->max <<= 1;
			pq->nodes = (PQnode *)alloc->memrealloc( alloc->userData, pq->nodes, 
				(size_t)((pq->max + 1) * sizeof( pq->nodes[0] )));
			if (pq->nodes == NULL) {
				pq->nodes = saveNodes;	// restore ptr to free upon return 
				return INV_HANDLE;
			}
			pq->handles = (PQhandleElem *)alloc->memrealloc( alloc->userData, pq->handles,
				(size_t) ((pq->max + 1) * sizeof( pq->handles[0] )));
			if (pq->handles == NULL) {
				pq->handles = saveHandles; // restore ptr to free upon return 
				return INV_HANDLE;
			}
		}
	}

	if( pq->freeList == 0 ) {
		free = curr;
	} else {
		free = pq->freeList;
		pq->freeList = pq->handles[free].node;
	}

	pq->nodes[curr].handle = free;
	pq->handles[free].node = curr;
	pq->handles[free].key = keyNew;

	if( pq->initialized ) {
		FloatUp( pq, curr );
	}
	assert(free != INV_HANDLE);
	return free;
}