#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* keys; struct TYPE_10__* order; int /*<<< orphan*/ * heap; } ;
struct TYPE_9__ {int /*<<< orphan*/  userData; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  TYPE_2__ PriorityQ ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqHeapDeletePriorityQ (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_2__*) ; 

void pqDeletePriorityQ( TESSalloc* alloc, PriorityQ *pq )
{
	assert(pq != NULL); 
	if (pq->heap != NULL) pqHeapDeletePriorityQ( alloc, pq->heap );
	if (pq->order != NULL) alloc->memfree( alloc->userData, pq->order );
	if (pq->keys != NULL) alloc->memfree( alloc->userData, pq->keys );
	alloc->memfree( alloc->userData, pq );
}