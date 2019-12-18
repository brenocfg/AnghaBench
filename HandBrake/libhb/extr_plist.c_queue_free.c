#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* head; } ;
typedef  TYPE_1__ queue_t ;
typedef  TYPE_1__ queue_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void queue_free(queue_t **_q)
{
    queue_t *q = *_q;
    if (q == NULL)
        return;

    queue_item_t *n, *i = q->head;
    while (i != NULL)
    {
        n = i->next;
        free(i);
        i = n;
    }
    free(q);
    *_q = NULL;
}