#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ link_state; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_12__ {int /*<<< orphan*/  state; int /*<<< orphan*/  adv_mode; } ;
typedef  TYPE_3__ tBTM_BLE_INQ_CB ;
struct TYPE_13__ {scalar_t__ link_role; } ;
typedef  TYPE_4__ tACL_CONN ;
struct TYPE_10__ {TYPE_3__ inq_var; } ;
struct TYPE_14__ {TYPE_1__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_ADV_DISABLE ; 
 int /*<<< orphan*/  BTM_BLE_STOP_ADV ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 scalar_t__ HCI_ROLE_SLAVE ; 
 scalar_t__ LST_CONNECTED ; 
 TYPE_4__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ btm_cb ; 
 int /*<<< orphan*/  btm_establish_continue (TYPE_4__*) ; 
 TYPE_2__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_process_fixed_chnl_resp (TYPE_2__*) ; 

void l2cble_notify_le_connection (BD_ADDR bda)
{
    tL2C_LCB *p_lcb = l2cu_find_lcb_by_bd_addr (bda, BT_TRANSPORT_LE);
    tACL_CONN *p_acl = btm_bda_to_acl(bda, BT_TRANSPORT_LE) ;

    if (p_lcb != NULL && p_acl != NULL && p_lcb->link_state != LST_CONNECTED) {

        if(p_acl->link_role == HCI_ROLE_SLAVE) {
            //clear p_cb->state, controller will stop adv when ble connected.
            tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;
            if(p_cb) {
                p_cb->adv_mode = BTM_BLE_ADV_DISABLE;
                p_cb->state = BTM_BLE_STOP_ADV;
            }
        }
        /* update link status */
        btm_establish_continue(p_acl);
        /* update l2cap link status and send callback */
        p_lcb->link_state = LST_CONNECTED;
        l2cu_process_fixed_chnl_resp (p_lcb);
    }
}