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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  dequeue_sem; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  enqueue_sem; } ;
typedef  TYPE_1__ fixed_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int list_append (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_give (int /*<<< orphan*/ *) ; 
 scalar_t__ osi_sem_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool fixed_queue_enqueue(fixed_queue_t *queue, void *data, uint32_t timeout)
{
    bool status=false; //Flag whether enqueued success

    assert(queue != NULL);
    assert(data != NULL);

    if (osi_sem_take(&queue->enqueue_sem, timeout) != 0) {
        return false;
    }

    osi_mutex_lock(&queue->lock, OSI_MUTEX_MAX_TIMEOUT);
    status = list_append(queue->list, data); //Check whether enqueued success 
    osi_mutex_unlock(&queue->lock);

    if(status == true )
        osi_sem_give(&queue->dequeue_sem);

    return status;
}