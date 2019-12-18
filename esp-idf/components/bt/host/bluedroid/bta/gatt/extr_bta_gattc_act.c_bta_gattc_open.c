#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
struct TYPE_13__ {int /*<<< orphan*/  layer_specific; } ;
struct TYPE_14__ {int /*<<< orphan*/  already_connect; TYPE_3__ hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  transport; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  remote_addr_type; } ;
struct TYPE_15__ {TYPE_4__ int_conn; TYPE_2__ api_conn; } ;
typedef  TYPE_5__ tBTA_GATTC_DATA ;
struct TYPE_16__ {int /*<<< orphan*/  bta_conn_id; TYPE_1__* p_rcb; } ;
typedef  TYPE_6__ tBTA_GATTC_CLCB ;
struct TYPE_11__ {int /*<<< orphan*/  client_if; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_GATTC_INT_CONN_EVT ; 
 int /*<<< orphan*/  BTA_GATTC_INT_OPEN_FAIL_EVT ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_Connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_GetConnIdIfConnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_gattc_sm_execute (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  gatt_find_specific_app_in_hold_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_gattc_open(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_DATA gattc_data;
    BOOLEAN found_app = FALSE;

    tGATT_TCB *p_tcb = gatt_find_tcb_by_addr(p_data->api_conn.remote_bda, BT_TRANSPORT_LE);
    if(p_tcb && p_clcb && p_data) {
        found_app = gatt_find_specific_app_in_hold_link(p_tcb, p_clcb->p_rcb->client_if);
    }
    /* open/hold a connection */
    if (!GATT_Connect(p_clcb->p_rcb->client_if, p_data->api_conn.remote_bda, p_data->api_conn.remote_addr_type,
                      TRUE, p_data->api_conn.transport)) {
        APPL_TRACE_ERROR("Connection open failure");

        bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_OPEN_FAIL_EVT, p_data);
    } else {
        /* a connected remote device */
        if (GATT_GetConnIdIfConnected(p_clcb->p_rcb->client_if,
                                      p_data->api_conn.remote_bda,
                                      &p_clcb->bta_conn_id,
                                      p_data->api_conn.transport)) {
            gattc_data.int_conn.hdr.layer_specific = p_clcb->bta_conn_id;
            gattc_data.int_conn.already_connect = found_app;
            bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_CONN_EVT, &gattc_data);
        }
        /* else wait for the callback event */
    }
}