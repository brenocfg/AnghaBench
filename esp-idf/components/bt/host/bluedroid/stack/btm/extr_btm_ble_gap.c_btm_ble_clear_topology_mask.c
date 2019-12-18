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
typedef  int /*<<< orphan*/  tBTM_BLE_STATE_MASK ;
struct TYPE_3__ {int /*<<< orphan*/  cur_states; } ;
struct TYPE_4__ {TYPE_1__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_STATE_ALL_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ btm_cb ; 

BOOLEAN btm_ble_clear_topology_mask (tBTM_BLE_STATE_MASK request_state_mask)
{
    request_state_mask &= BTM_BLE_STATE_ALL_MASK;
    btm_cb.ble_ctr_cb.cur_states &= ~request_state_mask;
    return TRUE;
}