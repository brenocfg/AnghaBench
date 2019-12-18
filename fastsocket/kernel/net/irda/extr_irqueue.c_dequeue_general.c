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
struct TYPE_7__ {struct TYPE_7__* q_next; TYPE_1__* q_prev; } ;
typedef  TYPE_2__ irda_queue_t ;
struct TYPE_6__ {TYPE_2__* q_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRDA_DEBUG (int,char*) ; 

__attribute__((used)) static irda_queue_t *dequeue_general(irda_queue_t **queue, irda_queue_t* element)
{
	irda_queue_t *ret;

	IRDA_DEBUG( 4, "dequeue_general()\n");

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
		 *  Remove specific element.
		 */
		element->q_prev->q_next = element->q_next;
		element->q_next->q_prev = element->q_prev;
		if ( (*queue) == element)
			(*queue) = element->q_next;
	}

	/*
	 * Return the removed entry (or NULL of queue was empty).
	 */
	return ret;
}