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
typedef  size_t UINT8 ;
struct TYPE_4__ {int /*<<< orphan*/  directed_conn; int /*<<< orphan*/  adv_mode; } ;
struct TYPE_5__ {scalar_t__* link_count; TYPE_1__ inq_var; } ;
struct TYPE_6__ {TYPE_2__ ble_ctr_cb; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_ADV_DISABLE ; 
 int /*<<< orphan*/  BTM_BLE_CONNECT_EVT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_ALL_ADV_MASK ; 
 int /*<<< orphan*/  BTM_BLE_STATE_ALL_CONN_MASK ; 
 int /*<<< orphan*/  BTM_BLE_STATE_MASTER_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_SLAVE_BIT ; 
 size_t HCI_ROLE_MASTER ; 
 size_t HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  btm_ble_clear_topology_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_set_topology_mask (int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 

void btm_ble_update_link_topology_mask(UINT8 link_role, BOOLEAN increase)
{
    btm_ble_clear_topology_mask (BTM_BLE_STATE_ALL_CONN_MASK);

    if (increase) {
        btm_cb.ble_ctr_cb.link_count[link_role]++;
    } else if (btm_cb.ble_ctr_cb.link_count[link_role] > 0) {
        btm_cb.ble_ctr_cb.link_count[link_role]--;
    }

    if (btm_cb.ble_ctr_cb.link_count[HCI_ROLE_MASTER]) {
        btm_ble_set_topology_mask (BTM_BLE_STATE_MASTER_BIT);
    }

    if (btm_cb.ble_ctr_cb.link_count[HCI_ROLE_SLAVE]) {
        btm_ble_set_topology_mask(BTM_BLE_STATE_SLAVE_BIT);
    }

    if (link_role == HCI_ROLE_SLAVE && increase) {
        btm_cb.ble_ctr_cb.inq_var.adv_mode = BTM_BLE_ADV_DISABLE;
        /* make device fall back into undirected adv mode by default */
        btm_cb.ble_ctr_cb.inq_var.directed_conn = BTM_BLE_CONNECT_EVT;
        /* clear all adv states */
        btm_ble_clear_topology_mask(BTM_BLE_STATE_ALL_ADV_MASK);
    }
}