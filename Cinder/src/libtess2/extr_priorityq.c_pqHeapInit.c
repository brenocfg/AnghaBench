#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_1__ PriorityQHeap ;

/* Variables and functions */
 int /*<<< orphan*/  FloatDown (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

void pqHeapInit( PriorityQHeap *pq )
{
	int i;

	/* This method of building a heap is O(n), rather than O(n lg n). */

	for( i = pq->size; i >= 1; --i ) {
		FloatDown( pq, i );
	}
	pq->initialized = TRUE;
}