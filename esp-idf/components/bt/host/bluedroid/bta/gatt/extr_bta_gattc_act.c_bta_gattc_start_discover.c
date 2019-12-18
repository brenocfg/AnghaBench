#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATTC_DATA ;
struct TYPE_13__ {scalar_t__ auto_update; scalar_t__ transport; scalar_t__ status; int /*<<< orphan*/  state; TYPE_7__* p_srcb; int /*<<< orphan*/  searched_service_source; int /*<<< orphan*/  disc_active; TYPE_2__* p_rcb; int /*<<< orphan*/  bta_conn_id; int /*<<< orphan*/ * p_q_cmd; } ;
typedef  TYPE_3__ tBTA_GATTC_CLCB ;
struct TYPE_11__ {scalar_t__ status; int /*<<< orphan*/  conn_id; } ;
struct TYPE_14__ {TYPE_1__ dis_cmpl; } ;
typedef  TYPE_4__ tBTA_GATTC ;
struct TYPE_15__ {scalar_t__ state; int /*<<< orphan*/  server_bda; scalar_t__ update_count; int /*<<< orphan*/  srvc_hdl_chg; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_GATTC_CONN_ST ; 
 scalar_t__ BTA_GATTC_DISC_WAITING ; 
 int /*<<< orphan*/  BTA_GATTC_DIS_SRVC_CMPL_EVT ; 
 scalar_t__ BTA_GATTC_NO_SCHEDULE ; 
 scalar_t__ BTA_GATTC_REQ_WAITING ; 
 int /*<<< orphan*/  BTA_GATTC_SERVICE_INFO_FROM_REMOTE_DEVICE ; 
 scalar_t__ BTA_GATTC_SERV_DISC ; 
 scalar_t__ BTA_GATTC_SERV_DISC_ACT ; 
 scalar_t__ BTA_GATTC_SERV_IDLE ; 
 scalar_t__ BTA_GATT_OK ; 
 scalar_t__ BTA_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_DISC_SRVC_ALL ; 
 int /*<<< orphan*/  L2CA_EnableUpdateBleConnParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ bta_gattc_discover_pri_service (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bta_gattc_init_cache (TYPE_7__*) ; 
 int /*<<< orphan*/  bta_gattc_reset_discover_st (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  bta_gattc_set_discover_st (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 

void bta_gattc_start_discover(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UNUSED(p_data);

    APPL_TRACE_DEBUG("bta_gattc_start_discover conn_id=%d p_clcb->p_srcb->state = %d ",
                     p_clcb->bta_conn_id, p_clcb->p_srcb->state);

    if (((p_clcb->p_q_cmd == NULL || p_clcb->auto_update == BTA_GATTC_REQ_WAITING) &&
            p_clcb->p_srcb->state == BTA_GATTC_SERV_IDLE) ||
            p_clcb->p_srcb->state == BTA_GATTC_SERV_DISC) {
        /* no pending operation, start discovery right away */
        p_clcb->auto_update = BTA_GATTC_NO_SCHEDULE;

        if (p_clcb->p_srcb != NULL) {
            /* clear the service change mask */
            p_clcb->p_srcb->srvc_hdl_chg = FALSE;
            p_clcb->p_srcb->update_count = 0;
            p_clcb->p_srcb->state = BTA_GATTC_SERV_DISC_ACT;

            if (p_clcb->transport == BTA_TRANSPORT_LE) {
                L2CA_EnableUpdateBleConnParams(p_clcb->p_srcb->server_bda, FALSE);
            }

            /* set all srcb related clcb into discovery ST */
            bta_gattc_set_discover_st(p_clcb->p_srcb);

            if ((p_clcb->status = bta_gattc_init_cache(p_clcb->p_srcb)) == BTA_GATT_OK) {
                p_clcb->status = bta_gattc_discover_pri_service(p_clcb->bta_conn_id,
                                 p_clcb->p_srcb, GATT_DISC_SRVC_ALL);
            }
            if (p_clcb->status != BTA_GATT_OK) {
                APPL_TRACE_ERROR("discovery on server failed");
                bta_gattc_reset_discover_st(p_clcb->p_srcb, p_clcb->status);
                //discover service complete, trigger callback
                tBTA_GATTC cb_data;
                cb_data.dis_cmpl.status  = p_clcb->status;
                cb_data.dis_cmpl.conn_id = p_clcb->bta_conn_id;
                ( *p_clcb->p_rcb->p_cback)(BTA_GATTC_DIS_SRVC_CMPL_EVT,  &cb_data);
            } else {
                p_clcb->disc_active = TRUE;
            }
            p_clcb->searched_service_source = BTA_GATTC_SERVICE_INFO_FROM_REMOTE_DEVICE;
        } else {
            APPL_TRACE_ERROR("unknown device, can not start discovery");
        }
    }
    /* pending operation, wait until it finishes */
    else {
        p_clcb->auto_update = BTA_GATTC_DISC_WAITING;

        if (p_clcb->p_srcb->state == BTA_GATTC_SERV_IDLE) {
            p_clcb->state = BTA_GATTC_CONN_ST;    /* set clcb state */
        }
    }

}