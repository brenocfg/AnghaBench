#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ first; } ;
struct TYPE_5__ {TYPE_4__ fifo; } ;
struct TYPE_6__ {TYPE_1__ queues; } ;
typedef  TYPE_2__ lwp_thrqueue ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_queue_isempty (TYPE_4__*) ; 

lwp_cntrl* __lwp_threadqueue_firstfifo(lwp_thrqueue *queue)
{
	if(!__lwp_queue_isempty(&queue->queues.fifo))
		return (lwp_cntrl*)queue->queues.fifo.first;

	return NULL;
}