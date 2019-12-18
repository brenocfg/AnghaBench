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
struct TYPE_6__ {scalar_t__ size; struct TYPE_6__* next; } ;
typedef  TYPE_1__ hb_buffer_t ;
struct TYPE_7__ {int count; int size; TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ hb_buffer_list_t ;

/* Variables and functions */

hb_buffer_t* hb_buffer_list_set(hb_buffer_list_t *list, hb_buffer_t *buf)
{
    int count = 0;
    int size = 0;

    if (list == NULL)
    {
        return NULL;
    }

    hb_buffer_t *head = list->head;
    hb_buffer_t *end = buf;
    if (end != NULL)
    {
        count++;
        size += end->size;
        while (end->next != NULL)
        {
            end = end->next;
            count++;
            size += end->size;
        }
    }
    list->head = buf;
    list->tail = end;
    list->count = count;
    list->size = size;
    return head;
}