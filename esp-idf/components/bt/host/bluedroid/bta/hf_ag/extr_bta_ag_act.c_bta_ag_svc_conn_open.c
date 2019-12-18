#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ call_ind; scalar_t__ callsetup_ind; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  app_id; int /*<<< orphan*/  peer_codecs; int /*<<< orphan*/  peer_features; int /*<<< orphan*/  act_timer; scalar_t__ bia_masked_out; scalar_t__ svc_conn; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
struct TYPE_7__ {int /*<<< orphan*/  app_id; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {int /*<<< orphan*/  peer_codec; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  peer_feat; TYPE_1__ hdr; } ;
typedef  TYPE_3__ tBTA_AG_CONN ;
typedef  int /*<<< orphan*/  tBTA_AG ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ BTA_AG_CALLSETUP_NONE ; 
 scalar_t__ BTA_AG_CALL_INACTIVE ; 
 int /*<<< orphan*/  BTA_AG_CONN_EVT ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_sys_sco_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bta_ag_svc_conn_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    tBTA_AG_CONN evt;
    UNUSED(p_data);

    if (!p_scb->svc_conn) {
        /* set state variable */
        p_scb->svc_conn = TRUE;
        /* Clear AT+BIA mask from previous SLC if any. */
        p_scb->bia_masked_out = 0;
        /* stop timer */
        bta_sys_stop_timer(&p_scb->act_timer);
        /* call callback */
        evt.hdr.handle = bta_ag_scb_to_idx(p_scb);
        evt.hdr.app_id = p_scb->app_id;
        evt.peer_feat = p_scb->peer_features;
        bdcpy(evt.bd_addr, p_scb->peer_addr);
#if (BTM_WBS_INCLUDED == TRUE )
        evt.peer_codec  = p_scb->peer_codecs;
#endif
        if ((p_scb->call_ind != BTA_AG_CALL_INACTIVE) ||
            (p_scb->callsetup_ind != BTA_AG_CALLSETUP_NONE)) {
            bta_sys_sco_use(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
        }
        (*bta_ag_cb.p_cback)(BTA_AG_CONN_EVT, (tBTA_AG *) &evt);
    }
}