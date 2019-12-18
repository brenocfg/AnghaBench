#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int client_if; scalar_t__ num_clcb; int /*<<< orphan*/  dereg_pending; } ;
typedef  TYPE_2__ tBTA_GATTC_RCB ;
typedef  int /*<<< orphan*/  tBTA_GATTC_DATA ;
struct TYPE_11__ {TYPE_8__* clcb; TYPE_1__* bg_track; } ;
typedef  TYPE_3__ tBTA_GATTC_CB ;
typedef  size_t UINT8 ;
struct TYPE_13__ {int /*<<< orphan*/  bta_conn_id; TYPE_2__* p_rcb; scalar_t__ in_use; } ;
struct TYPE_12__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_9__ {int cif_mask; int cif_adv_mask; int /*<<< orphan*/  remote_bda; scalar_t__ in_use; } ;
typedef  TYPE_4__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_GATTC_API_CLOSE_EVT ; 
 size_t BTA_GATTC_CLCB_MAX ; 
 size_t BTA_GATTC_KNOWN_SR_MAX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_CancelConnect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_gattc_close (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_gattc_deregister_cmpl (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_gattc_mark_bg_conn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_gattc_deregister(tBTA_GATTC_CB *p_cb, tBTA_GATTC_RCB  *p_clreg)
{
    UINT8               i;
    BT_HDR              buf;

    if (p_clreg != NULL) {
        /* remove bg connection associated with this rcb */
        for (i = 0; i < BTA_GATTC_KNOWN_SR_MAX; i ++) {
            if (p_cb->bg_track[i].in_use) {
                if (p_cb->bg_track[i].cif_mask & (1 << (p_clreg->client_if - 1))) {
                    bta_gattc_mark_bg_conn(p_clreg->client_if, p_cb->bg_track[i].remote_bda, FALSE, FALSE);
                    GATT_CancelConnect(p_clreg->client_if, p_cb->bg_track[i].remote_bda, FALSE);
                }
                if (p_cb->bg_track[i].cif_adv_mask & (1 << (p_clreg->client_if - 1))) {
                    bta_gattc_mark_bg_conn(p_clreg->client_if, p_cb->bg_track[i].remote_bda, FALSE, TRUE);
                }
            }
        }

        if (p_clreg->num_clcb > 0) {
            /* close all CLCB related to this app */
            for (i = 0; i < BTA_GATTC_CLCB_MAX; i ++) {
                if (p_cb->clcb[i].in_use && (p_cb->clcb[i].p_rcb == p_clreg)) {
                    p_clreg->dereg_pending = TRUE;

                    buf.event = BTA_GATTC_API_CLOSE_EVT;
                    buf.layer_specific = p_cb->clcb[i].bta_conn_id;
                    bta_gattc_close(&p_cb->clcb[i], (tBTA_GATTC_DATA *)&buf)  ;
                }
            }
        } else {
            bta_gattc_deregister_cmpl(p_clreg);
        }
    } else {
        APPL_TRACE_ERROR("bta_gattc_deregister Deregister Failedm unknown client cif");
    }
}