#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;
struct TYPE_7__ {int /*<<< orphan*/  chld_feat; int /*<<< orphan*/  peer_feat; } ;
typedef  TYPE_2__ tBTA_HF_CLIENT_CONN ;
typedef  int /*<<< orphan*/  evt ;
struct TYPE_6__ {int /*<<< orphan*/  chld_features; int /*<<< orphan*/  peer_features; scalar_t__ svc_conn; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_CONN_EVT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_5__ bta_hf_client_cb ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

void bta_hf_client_svc_conn_open(tBTA_HF_CLIENT_DATA *p_data)
{
    tBTA_HF_CLIENT_CONN evt;
    UNUSED(p_data);

    memset(&evt, 0, sizeof(evt));

    if (!bta_hf_client_cb.scb.svc_conn) {
        /* set state variable */
        bta_hf_client_cb.scb.svc_conn = TRUE;

        /* call callback */
        evt.peer_feat = bta_hf_client_cb.scb.peer_features;
        evt.chld_feat = bta_hf_client_cb.scb.chld_features;

        (*bta_hf_client_cb.p_cback)(BTA_HF_CLIENT_CONN_EVT, &evt);
    }
}