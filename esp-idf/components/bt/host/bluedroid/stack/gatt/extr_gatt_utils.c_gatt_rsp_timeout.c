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
struct TYPE_6__ {scalar_t__ operation; scalar_t__ op_subtype; scalar_t__ retry_count; int /*<<< orphan*/ * p_tcb; } ;
typedef  TYPE_1__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_7__ {scalar_t__ param; } ;
typedef  TYPE_2__ TIMER_LIST_ENT ;

/* Variables and functions */
 scalar_t__ GATTC_OPTYPE_DISCOVERY ; 
 scalar_t__ GATT_DISC_SRVC_ALL ; 
 scalar_t__ GATT_REQ_RETRY_LIMIT ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  gatt_act_discovery (TYPE_1__*) ; 
 TYPE_1__* gatt_cmd_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_disconnect (int /*<<< orphan*/ *) ; 

void gatt_rsp_timeout(TIMER_LIST_ENT *p_tle)
{
    tGATT_CLCB *p_clcb = (tGATT_CLCB *)p_tle->param;
    if (p_clcb == NULL || p_clcb->p_tcb == NULL) {
        GATT_TRACE_WARNING("gatt_rsp_timeout clcb is already deleted");
        return;
    }
    if (p_clcb->operation == GATTC_OPTYPE_DISCOVERY &&
            p_clcb->op_subtype == GATT_DISC_SRVC_ALL &&
            p_clcb->retry_count < GATT_REQ_RETRY_LIMIT) {
        UINT8 rsp_code;
        GATT_TRACE_WARNING("gatt_rsp_timeout retry discovery primary service");
        if (p_clcb != gatt_cmd_dequeue(p_clcb->p_tcb, &rsp_code)) {
            GATT_TRACE_ERROR("gatt_rsp_timeout command queue out of sync, disconnect");
        } else {
            p_clcb->retry_count++;
#if (GATTC_INCLUDED == TRUE)
            gatt_act_discovery(p_clcb);
#endif  ///GATTC_INCLUDED == TRUE
            return;
        }
    }

    GATT_TRACE_WARNING("gatt_rsp_timeout disconnecting...");
    gatt_disconnect (p_clcb->p_tcb);
}