#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t conn_service; int /*<<< orphan*/  conn_handle; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  peer_scn; int /*<<< orphan*/  cli_sec_mask; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_AG_MTU ; 
 int /*<<< orphan*/  BTA_AG_RFC_CLOSE_EVT ; 
 int /*<<< orphan*/  BTM_SEC_PROTO_RFCOMM ; 
 int /*<<< orphan*/  BTM_SetSecurityLevel (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_PSM_RFCOMM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PORT_SUCCESS ; 
 scalar_t__ RFCOMM_CreateConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bta_ag_mgmt_cback_tbl ; 
 int bta_ag_scb_to_idx (TYPE_1__*) ; 
 int /*<<< orphan*/ * bta_ag_sec_id ; 
 int /*<<< orphan*/  bta_ag_setup_port (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_sm_execute (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bta_ag_uuid ; 

void bta_ag_rfc_do_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    BTM_SetSecurityLevel(TRUE, "", bta_ag_sec_id[p_scb->conn_service],
        p_scb->cli_sec_mask, BT_PSM_RFCOMM, BTM_SEC_PROTO_RFCOMM, p_scb->peer_scn);

    if (RFCOMM_CreateConnection(bta_ag_uuid[p_scb->conn_service], p_scb->peer_scn,
            FALSE, BTA_AG_MTU, p_scb->peer_addr, &(p_scb->conn_handle),
            bta_ag_mgmt_cback_tbl[bta_ag_scb_to_idx(p_scb) - 1]) == PORT_SUCCESS) {
        bta_ag_setup_port(p_scb, p_scb->conn_handle);
        APPL_TRACE_DEBUG("bta_ag_rfc_do_open : conn_handle = %d", p_scb->conn_handle);
    } else {
        /* RFCOMM create connection failed; send ourselves RFCOMM close event */
        bta_ag_sm_execute(p_scb, BTA_AG_RFC_CLOSE_EVT, p_data);
    }
}