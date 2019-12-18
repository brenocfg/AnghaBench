#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* nodes; struct TYPE_9__* handles; } ;
struct TYPE_8__ {int /*<<< orphan*/  userData; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_1__ TESSalloc ;
typedef  TYPE_2__ PriorityQHeap ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_2__*) ; 

void pqHeapDeletePriorityQ( TESSalloc* alloc, PriorityQHeap *pq )
{
	alloc->memfree( alloc->userData, pq->handles );
	alloc->memfree( alloc->userData, pq->nodes );
	alloc->memfree( alloc->userData, pq );
}