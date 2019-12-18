#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ link_role; int /*<<< orphan*/  disc_reason; } ;
typedef  TYPE_1__ tL2C_LCB ;
struct TYPE_6__ {int* ble_connecting_bda; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BLE_CONN_CANCEL ; 
 scalar_t__ BLE_CONN_IDLE ; 
 scalar_t__ BTM_ACL_IS_CONNECTED (int*) ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  L2CAP_CONN_CANCEL ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ btm_ble_get_conn_st () ; 
 int /*<<< orphan*/  btm_ble_set_conn_st (int /*<<< orphan*/ ) ; 
 scalar_t__ btsnd_hcic_ble_create_conn_cancel () ; 
 TYPE_4__ l2cb ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_release_lcb (TYPE_1__*) ; 
 scalar_t__ memcmp (int*,int*,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_CancelBleConnectReq (BD_ADDR rem_bda)
{
    tL2C_LCB *p_lcb;

    /* There can be only one BLE connection request outstanding at a time */
    if (btm_ble_get_conn_st() == BLE_CONN_IDLE) {
        L2CAP_TRACE_WARNING ("L2CA_CancelBleConnectReq - no connection pending");
        return (FALSE);
    }

    if (memcmp (rem_bda, l2cb.ble_connecting_bda, BD_ADDR_LEN)) {
        L2CAP_TRACE_WARNING ("L2CA_CancelBleConnectReq - different  BDA Connecting: %08x%04x  Cancel: %08x%04x",
                             (l2cb.ble_connecting_bda[0] << 24) + (l2cb.ble_connecting_bda[1] << 16) + (l2cb.ble_connecting_bda[2] << 8) + l2cb.ble_connecting_bda[3],
                             (l2cb.ble_connecting_bda[4] << 8) + l2cb.ble_connecting_bda[5],
                             (rem_bda[0] << 24) + (rem_bda[1] << 16) + (rem_bda[2] << 8) + rem_bda[3], (rem_bda[4] << 8) + rem_bda[5]);

        return (FALSE);
    }

    if (btsnd_hcic_ble_create_conn_cancel()) {
        p_lcb = l2cu_find_lcb_by_bd_addr(rem_bda, BT_TRANSPORT_LE);
        /* Do not remove lcb if an LE link is already up as a peripheral */
        if (p_lcb != NULL &&
                !(p_lcb->link_role == HCI_ROLE_SLAVE && BTM_ACL_IS_CONNECTED(rem_bda))) {
            p_lcb->disc_reason = L2CAP_CONN_CANCEL;
            l2cu_release_lcb (p_lcb);
        }
        /* update state to be cancel, wait for connection cancel complete */
        btm_ble_set_conn_st (BLE_CONN_CANCEL);

        return (TRUE);
    } else {
        return (FALSE);
    }
}