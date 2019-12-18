#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ num_clcb; scalar_t__ dereg_pending; int /*<<< orphan*/  client_if; int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_7__*) ;} ;
typedef  TYPE_4__ tBTA_GATTC_RCB ;
struct TYPE_16__ {int /*<<< orphan*/  reason; } ;
struct TYPE_14__ {scalar_t__ event; int /*<<< orphan*/  layer_specific; } ;
struct TYPE_18__ {TYPE_3__ int_conn; TYPE_1__ hdr; } ;
typedef  TYPE_5__ tBTA_GATTC_DATA ;
struct TYPE_19__ {scalar_t__ transport; int /*<<< orphan*/  bda; int /*<<< orphan*/  status; int /*<<< orphan*/  reason; int /*<<< orphan*/  bta_conn_id; TYPE_4__* p_rcb; } ;
typedef  TYPE_6__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  (* tBTA_GATTC_CBACK ) (int /*<<< orphan*/ ,TYPE_7__*) ;
struct TYPE_15__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  status; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  client_if; } ;
struct TYPE_20__ {TYPE_2__ close; } ;
typedef  TYPE_7__ tBTA_GATTC ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_ALL_APP_ID ; 
 scalar_t__ BTA_GATTC_API_CLOSE_EVT ; 
 int /*<<< orphan*/  BTA_GATTC_CLOSE_EVT ; 
 scalar_t__ BTA_GATTC_INT_DISCONN_EVT ; 
 int /*<<< orphan*/  BTA_GATT_OK ; 
 int /*<<< orphan*/  BTA_ID_GATTC ; 
 scalar_t__ BTA_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  GATT_Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_clcb_dealloc (TYPE_6__*) ; 
 int /*<<< orphan*/  bta_gattc_deregister_cmpl (TYPE_4__*) ; 
 int /*<<< orphan*/  bta_sys_conn_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_7__*) ; 

void bta_gattc_close(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC_CBACK    *p_cback = p_clcb->p_rcb->p_cback;
    tBTA_GATTC_RCB      *p_clreg = p_clcb->p_rcb;
    tBTA_GATTC           cb_data;

    APPL_TRACE_DEBUG("bta_gattc_close conn_id=%d", p_clcb->bta_conn_id);

    cb_data.close.client_if = p_clcb->p_rcb->client_if;
    cb_data.close.conn_id   = p_clcb->bta_conn_id;
    cb_data.close.reason    = p_clcb->reason;
    cb_data.close.status    = p_clcb->status;
    bdcpy(cb_data.close.remote_bda, p_clcb->bda);

    if (p_clcb->transport == BTA_TRANSPORT_BR_EDR) {
        bta_sys_conn_close( BTA_ID_GATTC , BTA_ALL_APP_ID, p_clcb->bda);
    }

    bta_gattc_clcb_dealloc(p_clcb);

    if (p_data->hdr.event == BTA_GATTC_API_CLOSE_EVT) {
        cb_data.close.status = GATT_Disconnect(p_data->hdr.layer_specific);
    } else if (p_data->hdr.event == BTA_GATTC_INT_DISCONN_EVT) {
        cb_data.close.status = BTA_GATT_OK;
        cb_data.close.reason = p_data->int_conn.reason;
    }

    if (p_cback) {
        (* p_cback)(BTA_GATTC_CLOSE_EVT,   (tBTA_GATTC *)&cb_data);
    }

    if (p_clreg->num_clcb == 0 && p_clreg->dereg_pending) {
        bta_gattc_deregister_cmpl(p_clreg);
    }
}