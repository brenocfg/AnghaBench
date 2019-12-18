#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int open_services; scalar_t__ hsp_version; int /*<<< orphan*/  conn_service; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
struct TYPE_12__ {scalar_t__ status; } ;
struct TYPE_14__ {TYPE_1__ disc_result; } ;
typedef  TYPE_3__ tBTA_AG_DATA ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,scalar_t__) ; 
 scalar_t__ BTA_AG_DISC_FAIL_EVT ; 
 scalar_t__ BTA_AG_DISC_OK_EVT ; 
 int BTA_HFP_SERVICE_MASK ; 
 int BTA_HSP_SERVICE_MASK ; 
 scalar_t__ HSP_VERSION_1_0 ; 
 scalar_t__ HSP_VERSION_1_2 ; 
 scalar_t__ SDP_DB_FULL ; 
 scalar_t__ SDP_NO_RECS_MATCH ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  bta_ag_do_disc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bta_ag_free_db (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ bta_ag_sdp_find_attr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bta_ag_service_to_idx (int) ; 
 int /*<<< orphan*/  bta_ag_sm_execute (TYPE_2__*,scalar_t__,TYPE_3__*) ; 

void bta_ag_disc_int_res(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UINT16 event = BTA_AG_DISC_FAIL_EVT;
    APPL_TRACE_DEBUG ("bta_ag_disc_int_res: Status: %d", p_data->disc_result.status);

    /* if found service */
    if (p_data->disc_result.status == SDP_SUCCESS ||
        p_data->disc_result.status == SDP_DB_FULL) {
        /* get attributes */
        if (bta_ag_sdp_find_attr(p_scb, p_scb->open_services)) {
            /* set connected service */
            p_scb->conn_service = bta_ag_service_to_idx(p_scb->open_services);
            /* send ourselves sdp ok event */
            event = BTA_AG_DISC_OK_EVT;
        }
    }
    /* free discovery db */
    bta_ag_free_db(p_scb, p_data);
    /* if service not found check if we should search for other service */
    if ((event == BTA_AG_DISC_FAIL_EVT) &&
        (p_data->disc_result.status == SDP_SUCCESS ||
         p_data->disc_result.status == SDP_DB_FULL ||
         p_data->disc_result.status == SDP_NO_RECS_MATCH)) {
        if ((p_scb->open_services & BTA_HFP_SERVICE_MASK) &&
            (p_scb->open_services & BTA_HSP_SERVICE_MASK)) {
            /* search for HSP */
            p_scb->open_services &= ~BTA_HFP_SERVICE_MASK;
            bta_ag_do_disc(p_scb, p_scb->open_services);
        } else if ((p_scb->open_services & BTA_HSP_SERVICE_MASK) &&
                 (p_scb->hsp_version == HSP_VERSION_1_2)) {
            /* search for UUID_SERVCLASS_HEADSET for HSP 1.0 device */
            p_scb->hsp_version = HSP_VERSION_1_0;
            bta_ag_do_disc(p_scb, p_scb->open_services);
        } else {
            /* send ourselves sdp ok/fail event */
            bta_ag_sm_execute(p_scb, event, p_data);
        }
    } else {
        /* send ourselves sdp ok/fail event */
        bta_ag_sm_execute(p_scb, event, p_data);
    }
}