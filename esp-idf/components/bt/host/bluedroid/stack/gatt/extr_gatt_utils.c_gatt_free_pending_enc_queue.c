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
struct TYPE_3__ {int /*<<< orphan*/ * pending_enc_clcb; } ;
typedef  TYPE_1__ tGATT_TCB ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  fixed_queue_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

void gatt_free_pending_enc_queue(tGATT_TCB *p_tcb)
{
    GATT_TRACE_DEBUG("gatt_free_pending_enc_queue");
    if (p_tcb->pending_enc_clcb == NULL) {
        return;
    }

    /* release all queued indications */
    while (!fixed_queue_is_empty(p_tcb->pending_enc_clcb)) {
        osi_free(fixed_queue_dequeue(p_tcb->pending_enc_clcb, 0));
    }
	fixed_queue_free(p_tcb->pending_enc_clcb, NULL);
    p_tcb->pending_enc_clcb = NULL;
}