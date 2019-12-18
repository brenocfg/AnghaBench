#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  reg_services; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  hsp_version; int /*<<< orphan*/  svc_conn; scalar_t__ role; void* sco_codec; void* peer_codecs; scalar_t__ peer_features; scalar_t__ conn_service; scalar_t__ conn_handle; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 void* BTA_AG_CODEC_NONE ; 
 int /*<<< orphan*/  BTA_AG_FAIL_RFCOMM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HSP_VERSION_1_2 ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_addr_null ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_cback_open (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_start_servers (TYPE_1__*,int /*<<< orphan*/ ) ; 

void bta_ag_rfc_fail(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UNUSED(p_data);
    /* reinitialize stuff */
    p_scb->conn_handle = 0;
    p_scb->conn_service = 0;
    p_scb->peer_features = 0;
#if (BTM_WBS_INCLUDED == TRUE )
    p_scb->peer_codecs = BTA_AG_CODEC_NONE;
    p_scb->sco_codec = BTA_AG_CODEC_NONE;
#endif
    p_scb->role = 0;
    p_scb->svc_conn = FALSE;
    p_scb->hsp_version = HSP_VERSION_1_2;
    /*Clear the BD address*/
    bdcpy(p_scb->peer_addr, bd_addr_null);
    /* reopen registered servers */
    bta_ag_start_servers(p_scb, p_scb->reg_services);
    /* call open cback w. failure */
    bta_ag_cback_open(p_scb, NULL, BTA_AG_FAIL_RFCOMM);
}