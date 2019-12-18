#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error_code_app; scalar_t__ total_num; int /*<<< orphan*/ * queue; } ;
struct TYPE_5__ {TYPE_1__ prepare_write_record; } ;
typedef  TYPE_2__ tGATT_TCB ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  fixed_queue_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

void gatt_free_pending_prepare_write_queue(tGATT_TCB *p_tcb)
{
    GATT_TRACE_DEBUG("gatt_free_pending_prepare_write_queue");

    if (p_tcb->prepare_write_record.queue) {
        /* release all queued prepare write packets */
        while (!fixed_queue_is_empty(p_tcb->prepare_write_record.queue)) {
            osi_free(fixed_queue_dequeue(p_tcb->prepare_write_record.queue, FIXED_QUEUE_MAX_TIMEOUT));
        }
        fixed_queue_free(p_tcb->prepare_write_record.queue, NULL);
        p_tcb->prepare_write_record.queue = NULL;
    }

    p_tcb->prepare_write_record.total_num = 0;
    p_tcb->prepare_write_record.error_code_app = GATT_SUCCESS;
}