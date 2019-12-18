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
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  count; TYPE_1__* head; TYPE_1__* tail; } ;
typedef  TYPE_2__ hb_buffer_list_t ;

/* Variables and functions */

hb_buffer_t* hb_buffer_list_rem_head(hb_buffer_list_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    hb_buffer_t *head = list->head;
    if (list->head != NULL)
    {
        if (list->head == list->tail)
        {
            list->tail = NULL;
        }
        list->head = list->head->next;
        list->count--;
        list->size -= head->size;
    }
    if (head != NULL)
    {
        head->next = NULL;
    }
    return head;
}