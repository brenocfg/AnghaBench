#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  p_bda; int /*<<< orphan*/  handle; int /*<<< orphan*/  transport; } ;
struct TYPE_12__ {int /*<<< orphan*/  p_bda; int /*<<< orphan*/  hci_status; int /*<<< orphan*/  new_role; } ;
struct TYPE_11__ {int /*<<< orphan*/  busy_level_flags; int /*<<< orphan*/  busy_level; } ;
struct TYPE_10__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  transport; int /*<<< orphan*/  p_bda; } ;
struct TYPE_15__ {int event; TYPE_4__ conn; TYPE_3__ role_chg; TYPE_2__ update; TYPE_1__ discn; } ;
typedef  TYPE_6__ tBTM_BL_EVENT_DATA ;
struct TYPE_14__ {int /*<<< orphan*/  event; } ;
struct TYPE_16__ {int event; TYPE_5__ hdr; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  hci_status; int /*<<< orphan*/  new_role; int /*<<< orphan*/  busy_level_flags; int /*<<< orphan*/  busy_level; int /*<<< orphan*/  handle; int /*<<< orphan*/  transport; int /*<<< orphan*/  is_new; } ;
typedef  TYPE_7__ tBTA_DM_ACL_CHANGE ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_ACL_CHANGE_EVT ; 
#define  BTM_BL_COLLISION_EVT 132 
#define  BTM_BL_CONN_EVT 131 
#define  BTM_BL_DISCN_EVT 130 
#define  BTM_BL_ROLE_CHG_EVT 129 
#define  BTM_BL_UPDATE_EVT 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_7__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_dm_bl_change_cback (tBTM_BL_EVENT_DATA *p_data)
{
    tBTA_DM_ACL_CHANGE *p_msg;

    if ((p_msg = (tBTA_DM_ACL_CHANGE *) osi_malloc(sizeof(tBTA_DM_ACL_CHANGE))) != NULL) {
        p_msg->event = p_data->event;
        p_msg->is_new = FALSE;

        switch (p_msg->event) {
        case BTM_BL_CONN_EVT:
            p_msg->is_new = TRUE;
            bdcpy(p_msg->bd_addr, p_data->conn.p_bda);
#if BLE_INCLUDED == TRUE
            p_msg->transport = p_data->conn.transport;
            p_msg->handle = p_data->conn.handle;
#endif
            break;
        case BTM_BL_DISCN_EVT:
            bdcpy(p_msg->bd_addr, p_data->discn.p_bda);
#if BLE_INCLUDED == TRUE
            p_msg->transport = p_data->discn.transport;
            p_msg->handle = p_data->discn.handle;
#endif
            break;
        case BTM_BL_UPDATE_EVT:
            p_msg->busy_level = p_data->update.busy_level;
            p_msg->busy_level_flags = p_data->update.busy_level_flags;
            break;
        case BTM_BL_ROLE_CHG_EVT:
            p_msg->new_role = p_data->role_chg.new_role;
            p_msg->hci_status = p_data->role_chg.hci_status;
            bdcpy(p_msg->bd_addr, p_data->role_chg.p_bda);
            break;
        case BTM_BL_COLLISION_EVT:
            bdcpy(p_msg->bd_addr, p_data->conn.p_bda);
            break;
        }

        p_msg->hdr.event = BTA_DM_ACL_CHANGE_EVT;
        bta_sys_sendmsg(p_msg);

    }

}