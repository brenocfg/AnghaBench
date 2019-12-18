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
struct TYPE_5__ {int size; struct TYPE_5__* next; } ;
typedef  TYPE_1__ hb_buffer_t ;
struct TYPE_6__ {int count; int size; TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ hb_buffer_list_t ;

/* Variables and functions */

void hb_buffer_list_append(hb_buffer_list_t *list, hb_buffer_t *buf)
{
    int count = 1;
    int size = 0;
    hb_buffer_t *end = buf;

    if (buf == NULL)
    {
        return;
    }

    // Input buffer may be a list of buffers, find the end.
    size += buf->size;
    while (end != NULL && end->next != NULL)
    {
        end = end->next;
        size += end->size;
        count++;
    }
    if (list->tail == NULL)
    {
        list->head = buf;
        list->tail = end;
    }
    else
    {
        list->tail->next = buf;
        list->tail = end;
    }
    list->count += count;
    list->size += size;
}