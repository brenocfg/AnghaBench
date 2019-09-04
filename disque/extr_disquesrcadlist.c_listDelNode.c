#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  value; TYPE_1__* prev; TYPE_2__* next; } ;
typedef  TYPE_3__ listNode ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;TYPE_1__* tail; TYPE_2__* head; } ;
typedef  TYPE_4__ list ;
struct TYPE_9__ {TYPE_1__* prev; } ;
struct TYPE_8__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_3__*) ; 

void listDelNode(list *list, listNode *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;
    if (list->free) list->free(node->value);
    zfree(node);
    list->len--;
}