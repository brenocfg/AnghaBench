#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ status; TYPE_4__* p_cmpl; } ;
typedef  TYPE_5__ tBTA_GATTC_OP_CMPL ;
struct TYPE_18__ {scalar_t__ status; TYPE_3__* p_rcb; TYPE_2__* p_srcb; int /*<<< orphan*/  bta_conn_id; } ;
typedef  TYPE_6__ tBTA_GATTC_CLCB ;
struct TYPE_13__ {scalar_t__ status; int /*<<< orphan*/  mtu; int /*<<< orphan*/  conn_id; } ;
struct TYPE_19__ {TYPE_1__ cfg_mtu; } ;
typedef  TYPE_7__ tBTA_GATTC ;
struct TYPE_16__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_7__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_CFG_MTU_EVT ; 
 scalar_t__ BTA_GATT_OK ; 
 int /*<<< orphan*/  bta_gattc_free_command_data (TYPE_6__*) ; 
 int /*<<< orphan*/  bta_gattc_pop_command_to_send (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_7__*) ; 

void bta_gattc_cfg_mtu_cmpl(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_OP_CMPL *p_data)
{
    tBTA_GATTC          cb_data;
    //free the command data store in the queue.
    bta_gattc_free_command_data(p_clcb);
    bta_gattc_pop_command_to_send(p_clcb);

    if (p_data->p_cmpl  &&  p_data->status == BTA_GATT_OK) {
        p_clcb->p_srcb->mtu  = p_data->p_cmpl->mtu;
    }

    /* configure MTU complete, callback */
    p_clcb->status          = p_data->status;
    cb_data.cfg_mtu.conn_id = p_clcb->bta_conn_id;
    cb_data.cfg_mtu.status  = p_data->status;
    cb_data.cfg_mtu.mtu     = p_clcb->p_srcb->mtu;

    (*p_clcb->p_rcb->p_cback) (BTA_GATTC_CFG_MTU_EVT,  &cb_data);

}