#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* tqh_first; } ;
struct TYPE_10__ {TYPE_3__* tqe_next; } ;
struct TYPE_12__ {TYPE_1__ entries; } ;
struct TYPE_11__ {TYPE_8__ head; } ;
typedef  TYPE_2__ EventQueue ;
typedef  TYPE_3__ EventNode ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_8__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deleteNode (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void _glfwDeleteEventQueue(EventQueue* queue)
{
    if (queue)
    {
        EventNode* node, *node_next;
        node = queue->head.tqh_first;

        while (node != NULL)
        {
            node_next = node->entries.tqe_next;

            TAILQ_REMOVE(&queue->head, node, entries);
            deleteNode(queue, node);

            node = node_next;
        }

        free(queue);
    }
}