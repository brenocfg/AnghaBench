#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTA_SYS_CONN_STATUS ;
typedef  scalar_t__ tBTA_PREF_ROLES ;
struct TYPE_5__ {scalar_t__ conn_state; scalar_t__ pref_role; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ tBTA_DM_PEER_DEVICE ;
typedef  size_t UINT8 ;
struct TYPE_7__ {void* cur_av_count; } ;
struct TYPE_6__ {size_t app_id; size_t id; scalar_t__ cfg; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*,void*,scalar_t__) ; 
 scalar_t__ BTA_ALL_APP_ID ; 
 scalar_t__ BTA_DM_CONNECTED ; 
 int /*<<< orphan*/  BTA_DM_DI_AV_ACTIVE ; 
 scalar_t__ BTA_DM_UNPAIRING ; 
 size_t BTA_ID_AV ; 
 size_t BTA_ID_AVK ; 
 scalar_t__ BTA_SYS_CONN_BUSY ; 
 scalar_t__ BTA_SYS_CONN_IDLE ; 
 scalar_t__ BTA_SYS_CONN_OPEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bta_dm_adjust_roles (int /*<<< orphan*/ ) ; 
 TYPE_4__ bta_dm_cb ; 
 TYPE_1__* bta_dm_find_peer_device (int /*<<< orphan*/ ) ; 
 void* bta_dm_get_av_count () ; 
 TYPE_2__* p_bta_dm_rm_cfg ; 

__attribute__((used)) static void bta_dm_rm_cback(tBTA_SYS_CONN_STATUS status, UINT8 id, UINT8 app_id, BD_ADDR peer_addr)
{
    UINT8 j;
    tBTA_PREF_ROLES role;
    tBTA_DM_PEER_DEVICE *p_dev;

    p_dev = bta_dm_find_peer_device(peer_addr);
    if ( status == BTA_SYS_CONN_OPEN) {
        if (p_dev) {
            /* Do not set to connected if we are in the middle of unpairing. When AV stream is
             * started it fakes out a SYS_CONN_OPEN to potentially trigger a role switch command.
             * But this should not be done if we are in the middle of unpairing.
             */
            if (p_dev->conn_state != BTA_DM_UNPAIRING) {
                p_dev->conn_state = BTA_DM_CONNECTED;
            }

            for (j = 1; j <= p_bta_dm_rm_cfg[0].app_id; j++) {
                if (((p_bta_dm_rm_cfg[j].app_id == app_id) || (p_bta_dm_rm_cfg[j].app_id == BTA_ALL_APP_ID))
                        && (p_bta_dm_rm_cfg[j].id == id)) {
                    role = p_bta_dm_rm_cfg[j].cfg;

                    if (role > p_dev->pref_role ) {
                        p_dev->pref_role = role;
                    }
                    break;
                }
            }
        }
    }

    if ((BTA_ID_AV == id) || (BTA_ID_AVK == id)) {
        if ( status == BTA_SYS_CONN_BUSY) {
            if (p_dev) {
                p_dev->info |= BTA_DM_DI_AV_ACTIVE;
            }
            /* AV calls bta_sys_conn_open with the A2DP stream count as app_id */
            if (BTA_ID_AV == id) {
                bta_dm_cb.cur_av_count = bta_dm_get_av_count();
            }
        } else if ( status == BTA_SYS_CONN_IDLE) {
            if (p_dev) {
                p_dev->info &= ~BTA_DM_DI_AV_ACTIVE;
            }

            /* get cur_av_count from connected services */
            if (BTA_ID_AV == id) {
                bta_dm_cb.cur_av_count = bta_dm_get_av_count();
            }
        }
        APPL_TRACE_EVENT("bta_dm_rm_cback:%d, status:%d", bta_dm_cb.cur_av_count, status);
    }

    /* Don't adjust roles for each busy/idle state transition to avoid
       excessive switch requests when individual profile busy/idle status
       changes */
    if ((status != BTA_SYS_CONN_BUSY) && (status != BTA_SYS_CONN_IDLE)) {
        bta_dm_adjust_roles(FALSE);
    }
}