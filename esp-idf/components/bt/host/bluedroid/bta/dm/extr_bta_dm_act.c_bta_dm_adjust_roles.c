#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_9__ {int /*<<< orphan*/ * p_cback; } ;
struct TYPE_7__ {int count; int le_count; TYPE_1__* peer_device; } ;
struct TYPE_10__ {TYPE_4__ switch_delay_timer; TYPE_2__ device_list; scalar_t__ cur_av_count; } ;
struct TYPE_8__ {scalar_t__ cfg; } ;
struct TYPE_6__ {scalar_t__ conn_state; scalar_t__ transport; scalar_t__ pref_role; int /*<<< orphan*/  peer_bdaddr; } ;
typedef  int /*<<< orphan*/  TIMER_CBACK ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTA_ANY_ROLE ; 
 scalar_t__ BTA_DM_CONNECTED ; 
 scalar_t__ BTA_DM_NO_SCATTERNET ; 
 scalar_t__ BTA_DM_PARTIAL_SCATTERNET ; 
 scalar_t__ BTA_MASTER_ROLE_ONLY ; 
 scalar_t__ BTA_SLAVE_ROLE_ONLY ; 
 int /*<<< orphan*/  BTM_SwitchRole (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  L2CAP_DESIRED_LINK_ROLE ; 
 int /*<<< orphan*/  L2CA_SetDesireRole (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 TYPE_5__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_delay_role_switch_cback ; 
 int /*<<< orphan*/  bta_sys_start_timer (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* p_bta_dm_rm_cfg ; 

__attribute__((used)) static void bta_dm_adjust_roles(BOOLEAN delay_role_switch)
{

    UINT8 i;
    BOOLEAN set_master_role = FALSE;
#if BLE_INCLUDED == TRUE
    UINT8 br_count = bta_dm_cb.device_list.count - bta_dm_cb.device_list.le_count;
#else
    UINT8 br_count = bta_dm_cb.device_list.count;
#endif
    if (br_count) {

        /* the configuration is no scatternet
         * or AV connection exists and there are more than one ACL link */
        if ( (p_bta_dm_rm_cfg[0].cfg == BTA_DM_NO_SCATTERNET) ||
                (bta_dm_cb.cur_av_count && br_count > 1) ) {

            L2CA_SetDesireRole (HCI_ROLE_MASTER);
            set_master_role = TRUE;

        }

        for (i = 0; i < bta_dm_cb.device_list.count; i++) {
            if (bta_dm_cb.device_list.peer_device[i].conn_state == BTA_DM_CONNECTED
#if BLE_INCLUDED == TRUE
                    && bta_dm_cb.device_list.peer_device[i].transport == BT_TRANSPORT_BR_EDR
#endif
               ) {
                if (!set_master_role && (bta_dm_cb.device_list.peer_device[i].pref_role != BTA_ANY_ROLE)
                        && (p_bta_dm_rm_cfg[0].cfg == BTA_DM_PARTIAL_SCATTERNET)) {
                    L2CA_SetDesireRole (HCI_ROLE_MASTER);
                    set_master_role = TRUE;
                }

                if ((bta_dm_cb.device_list.peer_device[i].pref_role == BTA_MASTER_ROLE_ONLY)
                        || (br_count > 1)) {

                    /* Initiating immediate role switch with certain remote devices
                      has caused issues due to role  switch colliding with link encryption setup and
                      causing encryption (and in turn the link) to fail .  These device . Firmware
                      versions are stored in a blacklist and role switch with these devices are
                      delayed to avoid the collision with link encryption setup */

                    if (bta_dm_cb.device_list.peer_device[i].pref_role != BTA_SLAVE_ROLE_ONLY &&
                            delay_role_switch == FALSE) {
                        BTM_SwitchRole (bta_dm_cb.device_list.peer_device[i].peer_bdaddr,
                                        HCI_ROLE_MASTER, NULL);
                    } else {
                        bta_dm_cb.switch_delay_timer.p_cback =
                            (TIMER_CBACK *)&bta_dm_delay_role_switch_cback;
                        bta_sys_start_timer(&bta_dm_cb.switch_delay_timer, 0, 500);
                    }
                }

            }
        }


        if (!set_master_role) {

            L2CA_SetDesireRole (L2CAP_DESIRED_LINK_ROLE);

        }

    } else {
        L2CA_SetDesireRole (L2CAP_DESIRED_LINK_ROLE);
    }


}