#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cmd_max_len; TYPE_1__* p_user; int /*<<< orphan*/ * p_err_cback; int /*<<< orphan*/ * p_cmd_cback; int /*<<< orphan*/ * p_at_tbl; } ;
struct TYPE_8__ {int inband_enabled; int features; size_t conn_service; int /*<<< orphan*/  act_timer; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  app_id; int /*<<< orphan*/  air_mode; TYPE_7__ at_cb; void* cmee_enabled; void* cmer_enabled; void* ccwa_enabled; void* clip_enabled; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  tBTA_AG_AT_ERR_CBACK ;
typedef  int /*<<< orphan*/  tBTA_AG_AT_CMD_CBACK ;
typedef  int /*<<< orphan*/  tBTA_AG_AT_CMD ;
struct TYPE_9__ {int /*<<< orphan*/  conn_tout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_CMD_MAX ; 
 int BTA_AG_FEAT_INBAND ; 
 size_t BTA_AG_HFP ; 
 int /*<<< orphan*/  BTA_AG_SUCCESS ; 
 int /*<<< orphan*/  BTA_AG_SVC_TOUT_EVT ; 
 int /*<<< orphan*/  BTA_HFP_SCO_OUT_PKT_SIZE ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 void* FALSE ; 
 scalar_t__* bta_ag_at_cback_tbl ; 
 scalar_t__ bta_ag_at_err_cback ; 
 int /*<<< orphan*/  bta_ag_at_init (TYPE_7__*) ; 
 scalar_t__* bta_ag_at_tbl ; 
 int /*<<< orphan*/  bta_ag_cback_open (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_1__*) ; 
 int /*<<< orphan*/  bta_ag_sco_co_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_svc_conn_open (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bta_ag_svc_id ; 
 int /*<<< orphan*/  bta_sys_conn_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* p_bta_ag_cfg ; 

void bta_ag_rfc_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    /* initialize AT feature variables */
    p_scb->clip_enabled = FALSE;
    p_scb->ccwa_enabled = FALSE;
    p_scb->cmer_enabled = FALSE;
    p_scb->cmee_enabled = FALSE;
    p_scb->inband_enabled = ((p_scb->features & BTA_AG_FEAT_INBAND) == BTA_AG_FEAT_INBAND);

    /* set up AT command interpreter */
    p_scb->at_cb.p_at_tbl = (tBTA_AG_AT_CMD *) bta_ag_at_tbl[p_scb->conn_service];
    p_scb->at_cb.p_cmd_cback = (tBTA_AG_AT_CMD_CBACK *) bta_ag_at_cback_tbl[p_scb->conn_service];
    p_scb->at_cb.p_err_cback = (tBTA_AG_AT_ERR_CBACK *) bta_ag_at_err_cback;
    p_scb->at_cb.p_user = p_scb;
    p_scb->at_cb.cmd_max_len = BTA_AG_CMD_MAX;
    bta_ag_at_init(&p_scb->at_cb);

    /* call app open call-out */
    bta_ag_sco_co_open(bta_ag_scb_to_idx(p_scb), p_scb->air_mode, BTA_HFP_SCO_OUT_PKT_SIZE, bta_ag_svc_id[p_scb->conn_service]);
    bta_sys_conn_open(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
    bta_ag_cback_open(p_scb, NULL, BTA_AG_SUCCESS);

    if (p_scb->conn_service == BTA_AG_HFP) {
        /* if hfp start timer for service level conn */
        bta_sys_start_timer(&p_scb->act_timer, BTA_AG_SVC_TOUT_EVT, p_bta_ag_cfg->conn_tout);
    } else {
        /* else service level conn is open */
        bta_ag_svc_conn_open(p_scb, p_data);
    }
}