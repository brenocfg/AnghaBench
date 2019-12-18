#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* tail; TYPE_2__* head; } ;
typedef  TYPE_1__ list_t ;
struct TYPE_8__ {void* data; struct TYPE_8__* next; } ;
typedef  TYPE_2__ list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* list_free_node (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ list_is_empty (TYPE_1__*) ; 

bool list_remove(list_t *list, void *data)
{
    assert(list != NULL);
    assert(data != NULL);

    if (list_is_empty(list)) {
        return false;
    }

    if (list->head->data == data) {
        list_node_t *next = list_free_node(list, list->head);
        if (list->tail == list->head) {
            list->tail = next;
        }
        list->head = next;
        return true;
    }

    for (list_node_t *prev = list->head, *node = list->head->next; node; prev = node, node = node->next)
        if (node->data == data) {
            prev->next = list_free_node(list, node);
            if (list->tail == node) {
                list->tail = prev;
            }
            return true;
        }

    return false;
}