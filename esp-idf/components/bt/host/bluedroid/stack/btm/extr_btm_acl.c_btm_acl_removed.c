#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
struct TYPE_16__ {int sec_flags; } ;
typedef  TYPE_4__ tBTM_SEC_DEV_REC ;
struct TYPE_13__ {scalar_t__ transport; int /*<<< orphan*/  handle; int /*<<< orphan*/  p_bda; } ;
struct TYPE_17__ {TYPE_1__ discn; int /*<<< orphan*/  event; } ;
typedef  TYPE_5__ tBTM_BL_EVENT_DATA ;
struct TYPE_18__ {scalar_t__ transport; int /*<<< orphan*/  link_role; int /*<<< orphan*/  hci_handle; void* link_up_issued; void* in_use; } ;
typedef  TYPE_6__ tACL_CONN ;
struct TYPE_14__ {int /*<<< orphan*/  connectable_mode; } ;
struct TYPE_15__ {TYPE_2__ inq_var; } ;
struct TYPE_12__ {TYPE_3__ ble_ctr_cb; int /*<<< orphan*/  (* p_bl_changed_cb ) (TYPE_5__*) ;} ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLI_ACL_DOWN_EVT ; 
 int /*<<< orphan*/  BTM_BL_DISCN_EVT ; 
 int BTM_SEC_AUTHENTICATED ; 
 int BTM_SEC_AUTHORIZED ; 
 int BTM_SEC_ENCRYPTED ; 
 int BTM_SEC_LE_AUTHENTICATED ; 
 int BTM_SEC_LE_ENCRYPTED ; 
 int BTM_SEC_LE_LINK_KEY_AUTHED ; 
 int BTM_SEC_LE_LINK_KEY_KNOWN ; 
 int BTM_SEC_ROLE_SWITCHED ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 void* FALSE ; 
 int /*<<< orphan*/  HCI_ERR_NO_CONNECTION ; 
 int /*<<< orphan*/  btm_acl_report_role_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_acl_update_busy_level (int /*<<< orphan*/ ) ; 
 TYPE_6__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__ btm_cb ; 
 TYPE_4__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

void btm_acl_removed (BD_ADDR bda, tBT_TRANSPORT transport)
{
    tACL_CONN   *p;
    tBTM_BL_EVENT_DATA  evt_data;
#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC *p_dev_rec = NULL;
#endif
    BTM_TRACE_DEBUG ("btm_acl_removed\n");
    p = btm_bda_to_acl(bda, transport);
    if (p != (tACL_CONN *)NULL) {
        p->in_use = FALSE;

        /* if the disconnected channel has a pending role switch, clear it now */
        btm_acl_report_role_change(HCI_ERR_NO_CONNECTION, bda);

        /* Only notify if link up has had a chance to be issued */
        if (p->link_up_issued) {
            p->link_up_issued = FALSE;

            /* If anyone cares, tell him database changed */
            if (btm_cb.p_bl_changed_cb) {
                evt_data.event = BTM_BL_DISCN_EVT;
                evt_data.discn.p_bda = bda;
#if BLE_INCLUDED == TRUE
                evt_data.discn.handle = p->hci_handle;
                evt_data.discn.transport = p->transport;
#endif
                (*btm_cb.p_bl_changed_cb)(&evt_data);
            }

            btm_acl_update_busy_level (BTM_BLI_ACL_DOWN_EVT);
        }

#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)

        BTM_TRACE_DEBUG ("acl hci_handle=%d transport=%d connectable_mode=0x%0x link_role=%d\n",
                         p->hci_handle,
                         p->transport,
                         btm_cb.ble_ctr_cb.inq_var.connectable_mode,
                         p->link_role);

        p_dev_rec = btm_find_dev(bda);
        if ( p_dev_rec) {
            BTM_TRACE_DEBUG("before update p_dev_rec->sec_flags=0x%x\n", p_dev_rec->sec_flags);
            if (p->transport == BT_TRANSPORT_LE) {
                BTM_TRACE_DEBUG("LE link down\n");
                p_dev_rec->sec_flags &= ~(BTM_SEC_LE_ENCRYPTED | BTM_SEC_ROLE_SWITCHED);
                if ( (p_dev_rec->sec_flags & BTM_SEC_LE_LINK_KEY_KNOWN) == 0) {
                    BTM_TRACE_DEBUG("Not Bonded\n");
                    p_dev_rec->sec_flags &= ~(BTM_SEC_LE_LINK_KEY_AUTHED | BTM_SEC_LE_AUTHENTICATED);
                } else {
                    BTM_TRACE_DEBUG("Bonded\n");
                }
            } else {
                BTM_TRACE_DEBUG("Bletooth link down\n");
                p_dev_rec->sec_flags &= ~(BTM_SEC_AUTHORIZED | BTM_SEC_AUTHENTICATED
                                          | BTM_SEC_ENCRYPTED | BTM_SEC_ROLE_SWITCHED);
            }
            BTM_TRACE_DEBUG("after update p_dev_rec->sec_flags=0x%x\n", p_dev_rec->sec_flags);
        } else {
            BTM_TRACE_ERROR("Device not found\n");

        }
#endif

        /* Clear the ACL connection data */
        memset(p, 0, sizeof(tACL_CONN));
    }
}