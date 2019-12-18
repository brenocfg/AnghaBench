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
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int /*<<< orphan*/  tGATT_CL_COMPLETE ;
typedef  scalar_t__ tGATTC_OPTYPE ;
struct TYPE_3__ {scalar_t__ transport; int /*<<< orphan*/  bda; } ;
typedef  TYPE_1__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_ALL_APP_ID ; 
 int /*<<< orphan*/  BTA_ID_GATTC ; 
 scalar_t__ BTA_TRANSPORT_BR_EDR ; 
 scalar_t__ GATTC_OPTYPE_INDICATION ; 
 scalar_t__ GATTC_OPTYPE_NOTIFICATION ; 
 int /*<<< orphan*/  bta_gattc_cmpl_sendmsg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* bta_gattc_find_clcb_by_conn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_process_indicate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void  bta_gattc_cmpl_cback(UINT16 conn_id, tGATTC_OPTYPE op, tGATT_STATUS status,
                                  tGATT_CL_COMPLETE *p_data)
{
    tBTA_GATTC_CLCB     *p_clcb;
    APPL_TRACE_DEBUG("bta_gattc_cmpl_cback: conn_id = %d op = %d status = %d",
                     conn_id, op, status);

    /* notification and indication processed right away */
    if (op == GATTC_OPTYPE_NOTIFICATION || op == GATTC_OPTYPE_INDICATION) {
        bta_gattc_process_indicate(conn_id, op, p_data);
        return;
    }
    /* for all other operation, not expected if w/o connection */
    else if ((p_clcb = bta_gattc_find_clcb_by_conn_id(conn_id)) == NULL) {
        APPL_TRACE_ERROR("bta_gattc_cmpl_cback unknown conn_id =  %d, ignore data", conn_id);
        return;
    }

    /* if over BR_EDR, inform PM for mode change */
    if (p_clcb->transport == BTA_TRANSPORT_BR_EDR) {
        bta_sys_busy(BTA_ID_GATTC, BTA_ALL_APP_ID, p_clcb->bda);
        bta_sys_idle(BTA_ID_GATTC, BTA_ALL_APP_ID, p_clcb->bda);
    }

    bta_gattc_cmpl_sendmsg(conn_id, op, status, p_data);
}