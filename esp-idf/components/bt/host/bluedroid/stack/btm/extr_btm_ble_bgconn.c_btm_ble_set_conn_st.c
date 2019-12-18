#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_BLE_CONN_ST ;
struct TYPE_3__ {scalar_t__ conn_state; } ;
struct TYPE_4__ {TYPE_1__ ble_ctr_cb; } ;

/* Variables and functions */
 scalar_t__ BLE_BG_CONN ; 
 scalar_t__ BLE_DIR_CONN ; 
 int /*<<< orphan*/  BTM_BLE_STATE_INIT_BIT ; 
 int /*<<< orphan*/  btm_ble_clear_topology_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_set_topology_mask (int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 

void btm_ble_set_conn_st(tBTM_BLE_CONN_ST new_st)
{
    btm_cb.ble_ctr_cb.conn_state = new_st;

    if (new_st == BLE_BG_CONN || new_st == BLE_DIR_CONN) {
        btm_ble_set_topology_mask(BTM_BLE_STATE_INIT_BIT);
    } else {
        btm_ble_clear_topology_mask(BTM_BLE_STATE_INIT_BIT);
    }
}