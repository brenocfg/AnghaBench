#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ list_t ;
typedef  int /*<<< orphan*/  list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_free_node (TYPE_1__*,int /*<<< orphan*/ *) ; 

void list_clear(list_t *list)
{
    assert(list != NULL);
    for (list_node_t *node = list->head; node; ) {
        node = list_free_node(list, node);
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}