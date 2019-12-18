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
struct TYPE_27__ {scalar_t__ status; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  handle; TYPE_9__* p_value; } ;
struct TYPE_29__ {TYPE_7__ read; int /*<<< orphan*/  p_value; int /*<<< orphan*/  len; } ;
typedef  TYPE_9__ tBTA_GATT_UNFMT ;
struct TYPE_19__ {scalar_t__ status; TYPE_2__* p_cmpl; } ;
typedef  TYPE_10__ tBTA_GATTC_OP_CMPL ;
struct TYPE_20__ {TYPE_8__* p_rcb; int /*<<< orphan*/  bta_conn_id; TYPE_6__* p_q_cmd; } ;
typedef  TYPE_11__ tBTA_GATTC_CLCB ;
typedef  TYPE_9__ tBTA_GATTC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_28__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_9__*) ;} ;
struct TYPE_25__ {int /*<<< orphan*/  cmpl_evt; } ;
struct TYPE_24__ {int /*<<< orphan*/  cmpl_evt; int /*<<< orphan*/  handle; } ;
struct TYPE_23__ {scalar_t__ event; } ;
struct TYPE_26__ {TYPE_5__ api_read_multi; TYPE_4__ api_read; TYPE_3__ hdr; } ;
struct TYPE_21__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; int /*<<< orphan*/  handle; } ;
struct TYPE_22__ {TYPE_1__ att_value; } ;

/* Variables and functions */
 scalar_t__ BTA_GATTC_API_READ_MULTI_EVT ; 
 scalar_t__ BTA_GATT_OK ; 
 int /*<<< orphan*/  bta_gattc_free_command_data (TYPE_11__*) ; 
 int /*<<< orphan*/  bta_gattc_pop_command_to_send (TYPE_11__*) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_9__*) ; 

void bta_gattc_read_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_OP_CMPL *p_data)
{
    UINT8               event;
    tBTA_GATTC          cb_data;
    tBTA_GATT_UNFMT     read_value;

    memset(&cb_data, 0, sizeof(tBTA_GATTC));
    memset(&read_value, 0, sizeof(tBTA_GATT_UNFMT));

    cb_data.read.status     = p_data->status;

    if (p_data->p_cmpl != NULL && p_data->status == BTA_GATT_OK) {
        cb_data.read.handle = p_data->p_cmpl->att_value.handle;

        read_value.len = p_data->p_cmpl->att_value.len;
        read_value.p_value = p_data->p_cmpl->att_value.value;
        cb_data.read.p_value = &read_value;
    } else {
        cb_data.read.handle = p_clcb->p_q_cmd->api_read.handle;
    }

    if (p_clcb->p_q_cmd->hdr.event != BTA_GATTC_API_READ_MULTI_EVT) {
        event = p_clcb->p_q_cmd->api_read.cmpl_evt;
    } else {
        event = p_clcb->p_q_cmd->api_read_multi.cmpl_evt;
    }
    cb_data.read.conn_id = p_clcb->bta_conn_id;
    //free the command data store in the queue.
    bta_gattc_free_command_data(p_clcb);
    bta_gattc_pop_command_to_send(p_clcb);
    /* read complete, callback */
    ( *p_clcb->p_rcb->p_cback)(event, (tBTA_GATTC *)&cb_data);

}