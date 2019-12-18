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
 TYPE_2__* calloc (int,int) ; 

void queue_push_head(queue_t *q, void *v)
{
    queue_item_t *i = calloc(1, sizeof(queue_item_t));
    i->value = v;
    i->next = q->head;
    q->head = i;
}