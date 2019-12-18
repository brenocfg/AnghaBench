#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ transport; int /*<<< orphan*/  handle; int /*<<< orphan*/  p_features; int /*<<< orphan*/  p_dc; int /*<<< orphan*/  p_bdn; int /*<<< orphan*/  p_bda; } ;
struct TYPE_9__ {TYPE_1__ conn; int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ tBTM_BL_EVENT_DATA ;
struct TYPE_10__ {scalar_t__ transport; int /*<<< orphan*/  hci_handle; int /*<<< orphan*/ * peer_lmp_features; int /*<<< orphan*/  remote_dc; int /*<<< orphan*/  remote_name; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  link_up_issued; } ;
typedef  TYPE_3__ tACL_CONN ;
struct TYPE_11__ {int /*<<< orphan*/  (* p_bl_changed_cb ) (TYPE_2__*) ;scalar_t__ btm_def_link_policy; int /*<<< orphan*/  btm_acl_pkt_types_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLI_ACL_UP_EVT ; 
 int /*<<< orphan*/  BTM_BL_CONN_EVT ; 
 int /*<<< orphan*/  BTM_SetLinkPolicy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 size_t HCI_EXT_FEATURES_PAGE_0 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_acl_update_busy_level (int /*<<< orphan*/ ) ; 
 TYPE_7__ btm_cb ; 
 int /*<<< orphan*/  btm_set_packet_types (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void btm_establish_continue (tACL_CONN *p_acl_cb)
{
    tBTM_BL_EVENT_DATA  evt_data;
    BTM_TRACE_DEBUG ("btm_establish_continue\n");
#if (!defined(BTM_BYPASS_EXTRA_ACL_SETUP) || BTM_BYPASS_EXTRA_ACL_SETUP == FALSE)
#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)
    if (p_acl_cb->transport == BT_TRANSPORT_BR_EDR)
#endif
    {
        /* For now there are a some devices that do not like sending */
        /* commands events and data at the same time. */
        /* Set the packet types to the default allowed by the device */
        btm_set_packet_types (p_acl_cb, btm_cb.btm_acl_pkt_types_supported);

        if (btm_cb.btm_def_link_policy) {
            BTM_SetLinkPolicy (p_acl_cb->remote_addr, &btm_cb.btm_def_link_policy);
        }
    }
#endif
    p_acl_cb->link_up_issued = TRUE;

    /* If anyone cares, tell him database changed */
    if (btm_cb.p_bl_changed_cb) {
        evt_data.event = BTM_BL_CONN_EVT;
        evt_data.conn.p_bda = p_acl_cb->remote_addr;
        evt_data.conn.p_bdn = p_acl_cb->remote_name;
        evt_data.conn.p_dc  = p_acl_cb->remote_dc;
        evt_data.conn.p_features = p_acl_cb->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0];
#if BLE_INCLUDED == TRUE
        evt_data.conn.handle = p_acl_cb->hci_handle;
        evt_data.conn.transport = p_acl_cb->transport;
#endif

        (*btm_cb.p_bl_changed_cb)(&evt_data);
    }
    btm_acl_update_busy_level (BTM_BLI_ACL_UP_EVT);
}