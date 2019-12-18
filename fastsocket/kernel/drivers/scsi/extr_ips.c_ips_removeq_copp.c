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
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_1__ ips_copp_wait_item_t ;
struct TYPE_9__ {int /*<<< orphan*/  count; TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ ips_copp_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 TYPE_1__* ips_removeq_copp_head (TYPE_2__*) ; 

__attribute__((used)) static ips_copp_wait_item_t *
ips_removeq_copp(ips_copp_queue_t * queue, ips_copp_wait_item_t * item)
{
	ips_copp_wait_item_t *p;

	METHOD_TRACE("ips_removeq_copp", 1);

	if (!item)
		return (NULL);

	if (item == queue->head) {
		return (ips_removeq_copp_head(queue));
	}

	p = queue->head;

	while ((p) && (item != p->next))
		p = p->next;

	if (p) {
		/* found a match */
		p->next = item->next;

		if (!item->next)
			queue->tail = p;

		item->next = NULL;
		queue->count--;

		return (item);
	}

	return (NULL);
}