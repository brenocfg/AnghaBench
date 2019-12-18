#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ status; TYPE_3__* p_cmpl; } ;
typedef  TYPE_8__ tBTA_GATTC_OP_CMPL ;
struct TYPE_29__ {scalar_t__ svc_change_descr_handle; int /*<<< orphan*/  write_remote_svc_change_ccc_done; } ;
typedef  TYPE_9__ tBTA_GATTC_CONN ;
struct TYPE_19__ {TYPE_7__* p_rcb; int /*<<< orphan*/  bta_conn_id; TYPE_5__* p_q_cmd; int /*<<< orphan*/  bda; } ;
typedef  TYPE_10__ tBTA_GATTC_CLCB ;
struct TYPE_26__ {scalar_t__ status; scalar_t__ handle; int /*<<< orphan*/  conn_id; } ;
struct TYPE_20__ {TYPE_6__ write; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_11__ tBTA_GATTC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_27__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_11__*) ;} ;
struct TYPE_21__ {scalar_t__ event; } ;
struct TYPE_24__ {scalar_t__ write_type; int /*<<< orphan*/  cmpl_evt; int /*<<< orphan*/  p_value; TYPE_1__ hdr; } ;
struct TYPE_25__ {TYPE_4__ api_write; } ;
struct TYPE_22__ {scalar_t__ handle; int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct TYPE_23__ {TYPE_2__ att_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 scalar_t__ BTA_GATTC_API_WRITE_EVT ; 
 int /*<<< orphan*/  BTA_GATTC_PREP_WRITE_EVT ; 
 scalar_t__ BTA_GATTC_WRITE_PREPARE ; 
 scalar_t__ BTA_GATT_INVALID_PDU ; 
 scalar_t__ BTA_GATT_OK ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_9__* bta_gattc_conn_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_free_command_data (TYPE_10__*) ; 
 int /*<<< orphan*/  bta_gattc_pop_command_to_send (TYPE_10__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_11__*) ; 

void bta_gattc_write_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_OP_CMPL *p_data)
{
    tBTA_GATTC      cb_data = {0};
    UINT8          event;
    tBTA_GATTC_CONN *p_conn = bta_gattc_conn_find(p_clcb->bda);

    memset(&cb_data, 0, sizeof(tBTA_GATTC));

    cb_data.write.status     = p_data->status;
    cb_data.write.handle = p_data->p_cmpl->att_value.handle;
    if (p_clcb->p_q_cmd->api_write.hdr.event == BTA_GATTC_API_WRITE_EVT &&
        p_clcb->p_q_cmd->api_write.write_type == BTA_GATTC_WRITE_PREPARE) {
        // Should check the value received from the peer device is correct or not.
        if (memcmp(p_clcb->p_q_cmd->api_write.p_value, p_data->p_cmpl->att_value.value,
                   p_data->p_cmpl->att_value.len) != 0) {
            cb_data.write.status = BTA_GATT_INVALID_PDU;
        }

        event = BTA_GATTC_PREP_WRITE_EVT;
    } else {
        event = p_clcb->p_q_cmd->api_write.cmpl_evt;
    }
    //free the command data store in the queue.
    bta_gattc_free_command_data(p_clcb);
    bta_gattc_pop_command_to_send(p_clcb);
    cb_data.write.conn_id = p_clcb->bta_conn_id;
    if (p_conn && p_conn->svc_change_descr_handle == cb_data.write.handle) {
        if(cb_data.write.status != BTA_GATT_OK) {
            p_conn->write_remote_svc_change_ccc_done = FALSE;
            APPL_TRACE_ERROR("service change write ccc failed");
        }
        return;
    }
    /* write complete, callback */
    ( *p_clcb->p_rcb->p_cback)(event, (tBTA_GATTC *)&cb_data);

}