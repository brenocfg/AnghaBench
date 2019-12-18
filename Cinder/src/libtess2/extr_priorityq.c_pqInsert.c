#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int size; int max; int /*<<< orphan*/ * keys; int /*<<< orphan*/  heap; scalar_t__ initialized; } ;
struct TYPE_6__ {int /*<<< orphan*/  userData; scalar_t__ (* memrealloc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  TYPE_2__ PriorityQ ;
typedef  int /*<<< orphan*/  PQkey ;
typedef  int PQhandle ;

/* Variables and functions */
 int INV_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int pqHeapInsert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

PQhandle pqInsert( TESSalloc* alloc, PriorityQ *pq, PQkey keyNew )
{
	int curr;

	if( pq->initialized ) {
		return pqHeapInsert( alloc, pq->heap, keyNew );
	}
	curr = pq->size;
	if( ++ pq->size >= pq->max ) {
		if (!alloc->memrealloc)
		{
			return INV_HANDLE;
		}
		else
		{
			PQkey *saveKey= pq->keys;
			// If the heap overflows, double its size.
			pq->max <<= 1;
			pq->keys = (PQkey *)alloc->memrealloc( alloc->userData, pq->keys, 
				(size_t)(pq->max * sizeof( pq->keys[0] )));
			if (pq->keys == NULL) { 
				pq->keys = saveKey;  // restore ptr to free upon return 
				return INV_HANDLE;
			}
		}
	}
	assert(curr != INV_HANDLE); 
	pq->keys[curr] = keyNew;

	/* Negative handles index the sorted array. */
	return -(curr+1);
}