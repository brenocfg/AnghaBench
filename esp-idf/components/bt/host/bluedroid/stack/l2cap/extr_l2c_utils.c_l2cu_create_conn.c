#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ open_addr_type; scalar_t__ link_role; int /*<<< orphan*/  link_state; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  remote_bd_addr; scalar_t__ in_use; scalar_t__ transport; scalar_t__ ble_addr_type; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  scalar_t__ tBT_TRANSPORT ;
typedef  int /*<<< orphan*/  tBT_DEVICE_TYPE ;
typedef  scalar_t__ tBLE_ADDR_TYPE ;
struct TYPE_9__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;
struct TYPE_8__ {TYPE_1__* lcb_pool; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BLE_ADDR_PUBLIC ; 
 scalar_t__ BLE_ADDR_TYPE_MAX ; 
 scalar_t__ BLE_ADDR_UNKNOWN_TYPE ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ReadDevInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  BTM_ReadLocalFeatures () ; 
 scalar_t__ BTM_SwitchRole (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 scalar_t__ FALSE ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 scalar_t__ HCI_ROLE_SLAVE ; 
 scalar_t__ HCI_SWITCH_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_LINK_ROLE_SWITCH_TOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,char*) ; 
 int /*<<< orphan*/  LST_CONNECTING ; 
 int /*<<< orphan*/  LST_CONNECTING_WAIT_SWITCH ; 
 int MAX_L2CAP_LINKS ; 
 scalar_t__ TRUE ; 
 scalar_t__ btm_is_sco_active_by_bdaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* controller_get_interface () ; 
 TYPE_5__ l2cb ; 
 scalar_t__ l2cble_create_conn (TYPE_1__*) ; 
 scalar_t__ l2cu_create_conn_after_switch (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 () ; 

BOOLEAN l2cu_create_conn (tL2C_LCB *p_lcb, tBT_TRANSPORT transport)
{
    int             xx;
    tL2C_LCB        *p_lcb_cur = &l2cb.lcb_pool[0];
#if BTM_SCO_INCLUDED == TRUE
    BOOLEAN         is_sco_active;
#endif

#if (BLE_INCLUDED == TRUE)
    tBT_DEVICE_TYPE     dev_type;
    tBLE_ADDR_TYPE      addr_type = p_lcb->open_addr_type;
    if(addr_type == BLE_ADDR_UNKNOWN_TYPE) {
        BTM_ReadDevInfo(p_lcb->remote_bd_addr, &dev_type, &addr_type);
    }

    if (transport == BT_TRANSPORT_LE) {
        if (!controller_get_interface()->supports_ble()) {
            return FALSE;
        }
        if(addr_type > BLE_ADDR_TYPE_MAX) {
            addr_type = BLE_ADDR_PUBLIC;
        }
        p_lcb->ble_addr_type = addr_type;
        p_lcb->transport = BT_TRANSPORT_LE;

        return (l2cble_create_conn(p_lcb));
    }
#endif

    /* If there is a connection where we perform as a slave, try to switch roles
       for this connection */
    for (xx = 0, p_lcb_cur = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb_cur++) {
        if (p_lcb_cur == p_lcb) {
            continue;
        }

        if ((p_lcb_cur->in_use) && (p_lcb_cur->link_role == HCI_ROLE_SLAVE)) {

#if BTM_SCO_INCLUDED == TRUE
            /* The LMP_switch_req shall be sent only if the ACL logical transport
            is in active mode, when encryption is disabled, and all synchronous
            logical transports on the same physical link are disabled." */

            /* Check if there is any SCO Active on this BD Address */
            is_sco_active = btm_is_sco_active_by_bdaddr(p_lcb_cur->remote_bd_addr);

            L2CAP_TRACE_API ("l2cu_create_conn - btm_is_sco_active_by_bdaddr() is_sco_active = %s", \
                             (is_sco_active == TRUE) ? "TRUE" : "FALSE");

            if (is_sco_active == TRUE) {
                continue;    /* No Master Slave switch not allowed when SCO Active */
            }
#endif
            /*4_1_TODO check  if btm_cb.devcb.local_features to be used instead */
            if (HCI_SWITCH_SUPPORTED(BTM_ReadLocalFeatures())) {
                /* mark this lcb waiting for switch to be completed and
                   start switch on the other one */
                p_lcb->link_state = LST_CONNECTING_WAIT_SWITCH;
                p_lcb->link_role  = HCI_ROLE_MASTER;

                if (BTM_SwitchRole (p_lcb_cur->remote_bd_addr, HCI_ROLE_MASTER, NULL) == BTM_CMD_STARTED) {
                    btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_ROLE_SWITCH_TOUT);
                    return (TRUE);
                }
            }
        }
    }

    p_lcb->link_state = LST_CONNECTING;

    return (l2cu_create_conn_after_switch (p_lcb));
}