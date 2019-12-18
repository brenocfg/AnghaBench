#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  size_t UINT8 ;
struct TYPE_11__ {int param; int /*<<< orphan*/ * p_cback; } ;
struct TYPE_9__ {size_t count; TYPE_1__* peer_device; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;void* disabling; TYPE_4__ disable_timer; TYPE_2__ device_list; } ;
struct TYPE_10__ {scalar_t__ param; } ;
struct TYPE_8__ {int /*<<< orphan*/  peer_bdaddr; int /*<<< orphan*/  transport; } ;
typedef  TYPE_3__ TIMER_LIST_ENT ;
typedef  int /*<<< orphan*/  TIMER_CBACK ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*,scalar_t__) ; 
 int /*<<< orphan*/  BTA_DM_DISABLE_EVT ; 
 scalar_t__ BTM_GetNumAclLinks () ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  UNUSED (TYPE_3__*) ; 
 int /*<<< orphan*/  UUID_SERVCLASS_PNP_INFORMATION ; 
 TYPE_6__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_sys_remove_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_start_timer (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btm_remove_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_dm_disable_timer_cback (TIMER_LIST_ENT *p_tle)
{
    UNUSED(p_tle);
    UINT8 i;
    tBT_TRANSPORT transport = BT_TRANSPORT_BR_EDR;
    BOOLEAN trigger_disc = FALSE;


    APPL_TRACE_EVENT(" bta_dm_disable_timer_cback trial %d ", p_tle->param);

    if (BTM_GetNumAclLinks() && p_tle->param == 0) {
        for (i = 0; i < bta_dm_cb.device_list.count; i++) {
#if (BLE_INCLUDED == TRUE)
            transport = bta_dm_cb.device_list.peer_device[i].transport;
#endif
            btm_remove_acl(bta_dm_cb.device_list.peer_device[i].peer_bdaddr, transport);
            trigger_disc = TRUE;
        }

        /* Retrigger disable timer in case ACL disconnect failed, DISABLE_EVT still need
            to be sent out to avoid jave layer disable timeout */
        if (trigger_disc) {
            bta_dm_cb.disable_timer.p_cback = (TIMER_CBACK *)&bta_dm_disable_timer_cback;
            bta_dm_cb.disable_timer.param = 1;
            bta_sys_start_timer(&bta_dm_cb.disable_timer, 0, 1500);
        }
    } else {
        bta_dm_cb.disabling = FALSE;

        bta_sys_remove_uuid(UUID_SERVCLASS_PNP_INFORMATION);
        bta_dm_cb.p_sec_cback(BTA_DM_DISABLE_EVT, NULL);
    }
}