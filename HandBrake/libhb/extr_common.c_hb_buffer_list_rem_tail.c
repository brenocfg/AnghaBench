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
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ size; } ;
typedef  TYPE_1__ hb_buffer_t ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ count; TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ hb_buffer_list_t ;

/* Variables and functions */

hb_buffer_t* hb_buffer_list_rem_tail(hb_buffer_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    hb_buffer_t *tail = list->tail;

    if (list->head == list->tail)
    {
        list->head = list->tail = NULL;
        list->count = 0;
        list->size = 0;
    }
    else if (list->tail != NULL)
    {
        hb_buffer_t *end = list->head;
        while (end->next != list->tail)
        {
            end = end->next;
        }
        end->next = NULL;
        list->tail = end;
        list->count--;
        list->size -= tail->size;
    }
    if (tail != NULL)
    {
        tail->next = NULL;
    }
    return tail;
}