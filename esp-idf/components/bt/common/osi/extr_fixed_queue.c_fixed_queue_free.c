#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dequeue_sem; int /*<<< orphan*/  enqueue_sem; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ fixed_queue_t ;
typedef  int /*<<< orphan*/  (* fixed_queue_free_cb ) (int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_queue_unregister_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  osi_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_free (int /*<<< orphan*/ *) ; 

void fixed_queue_free(fixed_queue_t *queue, fixed_queue_free_cb free_cb)
{
    const list_node_t *node;

    if (queue == NULL) {
	    return;
	}

    fixed_queue_unregister_dequeue(queue);

    if (free_cb) {
        for (node = list_begin(queue->list); node != list_end(queue->list); node = list_next(node)) {
            free_cb(list_node(node));
        }
    }

    list_free(queue->list);
    osi_sem_free(&queue->enqueue_sem);
    osi_sem_free(&queue->dequeue_sem);
    osi_mutex_free(&queue->lock);
    osi_free(queue);
}