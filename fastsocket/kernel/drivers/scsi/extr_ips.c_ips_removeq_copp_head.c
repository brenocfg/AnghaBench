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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ ips_copp_wait_item_t ;
struct TYPE_6__ {int /*<<< orphan*/  count; TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ ips_copp_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 

__attribute__((used)) static ips_copp_wait_item_t *
ips_removeq_copp_head(ips_copp_queue_t * queue)
{
	ips_copp_wait_item_t *item;

	METHOD_TRACE("ips_removeq_copp_head", 1);

	item = queue->head;

	if (!item) {
		return (NULL);
	}

	queue->head = item->next;
	item->next = NULL;

	if (queue->tail == item)
		queue->tail = NULL;

	queue->count--;

	return (item);
}