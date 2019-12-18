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
struct TYPE_5__ {TYPE_2__* head; } ;
typedef  TYPE_1__ queue_t ;
struct TYPE_6__ {struct TYPE_6__* next; void* value; } ;
typedef  TYPE_2__ queue_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void * queue_pop_head(queue_t *q)
{
    void *result;
    queue_item_t *i;

    if (q->head == NULL)
        return NULL;

    i = q->head;
    result = i->value;
    q->head = i->next;
    free(i);

    return result;
}