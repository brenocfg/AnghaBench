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
struct TYPE_8__ {struct TYPE_8__* next; scalar_t__ size; } ;
typedef  TYPE_1__ hb_buffer_t ;
struct TYPE_9__ {TYPE_1__* tail; int /*<<< orphan*/  size; int /*<<< orphan*/  count; TYPE_1__* head; } ;
typedef  TYPE_2__ hb_buffer_list_t ;

/* Variables and functions */
 TYPE_1__* hb_buffer_list_rem_head (TYPE_2__*) ; 

hb_buffer_t* hb_buffer_list_rem(hb_buffer_list_t *list, hb_buffer_t * b)
{
    hb_buffer_t * a;

    if (list == NULL)
    {
        return NULL;
    }
    if (b == list->head)
    {
        return hb_buffer_list_rem_head(list);
    }
    a = list->head;
    while (a != NULL && a->next != b)
    {
        a = a->next;
    }
    if (a == NULL)
    {
        // Buffer is not in the list
        return NULL;
    }
    list->count--;
    list->size -= b->size;
    a->next = b->next;
    if (list->tail == b)
    {
        list->tail = a;
    }
    b->next = NULL;

    return b;
}