#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; int /*<<< orphan*/  handle; int /*<<< orphan*/  conn_id; } ;
typedef  TYPE_1__ tGATT_VALUE ;
struct TYPE_6__ {int /*<<< orphan*/  pending_ind_q; } ;
typedef  TYPE_2__ tGATT_TCB ;

/* Variables and functions */
 int /*<<< orphan*/  GATTS_HandleValueIndication (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 scalar_t__ fixed_queue_try_peek_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_try_remove_from_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gatts_chk_pending_ind(tGATT_TCB *p_tcb )
{
#if (GATTS_INCLUDED == TRUE)
    tGATT_VALUE *p_buf = (tGATT_VALUE *)fixed_queue_try_peek_first(p_tcb->pending_ind_q);
    GATT_TRACE_DEBUG("gatts_chk_pending_ind");

    if (p_buf ) {
        GATTS_HandleValueIndication (p_buf->conn_id,
                                     p_buf->handle,
                                     p_buf->len,
                                     p_buf->value);
        osi_free(fixed_queue_try_remove_from_queue(p_tcb->pending_ind_q,
                                                      p_buf));
    }
#endif  ///GATTS_INCLUDED == TRUE
}