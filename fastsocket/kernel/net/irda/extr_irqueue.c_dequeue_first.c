#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* q_next; TYPE_1__* q_prev; } ;
typedef  TYPE_2__ irda_queue_t ;
struct TYPE_5__ {TYPE_2__* q_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRDA_DEBUG (int,char*) ; 

__attribute__((used)) static irda_queue_t *dequeue_first(irda_queue_t **queue)
{
	irda_queue_t *ret;

	IRDA_DEBUG( 4, "dequeue_first()\n");

	/*
	 * Set return value
	 */
	ret =  *queue;

	if ( *queue == NULL ) {
		/*
		 * Queue was empty.
		 */
	} else if ( (*queue)->q_next == *queue ) {
		/*
		 *  Queue only contained a single element. It will now be
		 *  empty.
		 */
		*queue = NULL;
	} else {
		/*
		 * Queue contained several element.  Remove the first one.
		 */
		(*queue)->q_prev->q_next = (*queue)->q_next;
		(*queue)->q_next->q_prev = (*queue)->q_prev;
		*queue = (*queue)->q_next;
	}

	/*
	 * Return the removed entry (or NULL of queue was empty).
	 */
	return ret;
}