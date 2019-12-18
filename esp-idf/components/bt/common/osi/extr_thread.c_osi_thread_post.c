#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* context; int /*<<< orphan*/ * func; } ;
typedef  TYPE_1__ work_item_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int work_queue_num; int /*<<< orphan*/  work_sem; int /*<<< orphan*/ * work_queues; } ;
typedef  TYPE_2__ osi_thread_t ;
typedef  int /*<<< orphan*/ * osi_thread_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 
 scalar_t__ osi_malloc (int) ; 
 int /*<<< orphan*/  osi_sem_give (int /*<<< orphan*/ *) ; 

bool osi_thread_post(osi_thread_t *thread, osi_thread_func_t func, void *context, int queue_idx, uint32_t timeout)
{
    assert(thread != NULL);
    assert(func != NULL);

    if (queue_idx >= thread->work_queue_num) {
        return false;
    }

    work_item_t *item = (work_item_t *)osi_malloc(sizeof(work_item_t));
    if (item == NULL) {
        return false;
    }
    item->func = func;
    item->context = context;

    if (fixed_queue_enqueue(thread->work_queues[queue_idx], item, timeout) == false) {
        osi_free(item);
        return false;
    }

    osi_sem_give(&thread->work_sem);

    return true;
}