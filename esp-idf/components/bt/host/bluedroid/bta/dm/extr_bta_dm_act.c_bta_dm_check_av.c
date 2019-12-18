#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_5__ {scalar_t__ conn_state; int info; int /*<<< orphan*/  peer_bdaddr; } ;
typedef  TYPE_2__ tBTA_DM_PEER_DEVICE ;
typedef  size_t UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {size_t count; TYPE_2__* peer_device; } ;
struct TYPE_6__ {scalar_t__ rs_event; TYPE_1__ device_list; scalar_t__ cur_av_count; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*,scalar_t__) ; 
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*,size_t,scalar_t__,int,scalar_t__) ; 
 scalar_t__ BTA_DM_API_SEARCH_EVT ; 
 scalar_t__ BTA_DM_CONNECTED ; 
 int BTA_DM_DI_AV_ACTIVE ; 
 int /*<<< orphan*/  BTA_SYS_PLCY_CLR ; 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_SwitchRole (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HCI_ENABLE_MASTER_SLAVE_SWITCH ; 
 int /*<<< orphan*/  HCI_ROLE_MASTER ; 
 scalar_t__ TRUE ; 
 TYPE_3__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_policy_cback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bta_dm_rs_cback ; 

__attribute__((used)) static BOOLEAN bta_dm_check_av(UINT16 event)
{
    BOOLEAN avoid_roleswitch = FALSE;
    BOOLEAN switching = FALSE;
    UINT8 i;
    tBTA_DM_PEER_DEVICE *p_dev;

#if defined(BTA_DM_AVOID_A2DP_ROLESWITCH_ON_INQUIRY) && (BTA_DM_AVOID_A2DP_ROLESWITCH_ON_INQUIRY == TRUE)

    /* avoid role switch upon inquiry if a2dp is actively streaming as it
       introduces an audioglitch due to FW scheduling delays (unavoidable) */
    if (event == BTA_DM_API_SEARCH_EVT) {
        avoid_roleswitch = TRUE;
    }
#endif

    APPL_TRACE_EVENT("bta_dm_check_av:%d", bta_dm_cb.cur_av_count);
    if (bta_dm_cb.cur_av_count) {
        for (i = 0; i < bta_dm_cb.device_list.count; i++) {
            p_dev = &bta_dm_cb.device_list.peer_device[i];
            APPL_TRACE_WARNING("[%d]: state:%d, info:x%x, avoid_rs %d",
                               i, p_dev->conn_state, p_dev->info, avoid_roleswitch);
            if ((p_dev->conn_state == BTA_DM_CONNECTED) && (p_dev->info & BTA_DM_DI_AV_ACTIVE) &&
                    (avoid_roleswitch == FALSE)) {
                /* make master and take away the role switch policy */
                if (BTM_CMD_STARTED == BTM_SwitchRole (p_dev->peer_bdaddr, HCI_ROLE_MASTER, (tBTM_CMPL_CB *)bta_dm_rs_cback)) {
                    /* the role switch command is actually sent */
                    bta_dm_cb.rs_event = event;
                    switching = TRUE;
                }
                /* else either already master or can not switch for some reasons */
                bta_dm_policy_cback(BTA_SYS_PLCY_CLR, 0, HCI_ENABLE_MASTER_SLAVE_SWITCH, p_dev->peer_bdaddr);
                break;
            }
        }
    }
    return switching;
}