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
struct TYPE_5__ {size_t capacity; int /*<<< orphan*/  dequeue_sem; int /*<<< orphan*/  enqueue_sem; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ fixed_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_queue_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_new (int /*<<< orphan*/ *) ; 
 TYPE_1__* osi_calloc (int) ; 
 int /*<<< orphan*/  osi_mutex_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_new (int /*<<< orphan*/ *,size_t,size_t) ; 

fixed_queue_t *fixed_queue_new(size_t capacity)
{
    fixed_queue_t *ret = osi_calloc(sizeof(fixed_queue_t));
    if (!ret) {
        goto error;
    }

    osi_mutex_new(&ret->lock);
    ret->capacity = capacity;

    ret->list = list_new(NULL);
    if (!ret->list) {
        goto error;
    }


    osi_sem_new(&ret->enqueue_sem, capacity, capacity);
    if (!ret->enqueue_sem) {
        goto error;
    }

    osi_sem_new(&ret->dequeue_sem, capacity, 0);
    if (!ret->dequeue_sem) {
        goto error;
    }

    return ret;

error:;
    fixed_queue_free(ret, NULL);
    return NULL;
}