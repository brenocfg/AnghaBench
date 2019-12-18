#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  enqueue_sem; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  dequeue_sem; } ;
typedef  TYPE_1__ fixed_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ list_contains (int /*<<< orphan*/ ,void*) ; 
 int list_remove (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_give (int /*<<< orphan*/ ) ; 
 scalar_t__ osi_sem_take (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *fixed_queue_try_remove_from_queue(fixed_queue_t *queue, void *data)
{
    bool removed = false;

    if (queue == NULL) {
        return NULL;
    }

    osi_mutex_lock(&queue->lock, OSI_MUTEX_MAX_TIMEOUT);
    if (list_contains(queue->list, data) &&
            osi_sem_take(queue->dequeue_sem, 0) == 0) {
        removed = list_remove(queue->list, data);
        assert(removed);
    }
    osi_mutex_unlock(&queue->lock);

    if (removed) {
        osi_sem_give(queue->enqueue_sem);
        return data;
    }

    return NULL;
}