#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_5__ {int /*<<< orphan*/  exist_addr_bit; int /*<<< orphan*/  static_rand_addr; int /*<<< orphan*/  private_addr; } ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_7__ {TYPE_1__ addr_mgnt_cb; TYPE_2__ inq_var; } ;
struct TYPE_8__ {TYPE_3__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_BLE_GAP_ADDR_BIT_RANDOM ; 
 scalar_t__ BTM_BLE_IDLE ; 
 scalar_t__ BTM_BLE_STOP_ADV ; 
 scalar_t__ BTM_BLE_STOP_SCAN ; 
 int /*<<< orphan*/  BTM_SET_STATIC_RAND_ADDR_FAIL ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,scalar_t__) ; 
 TYPE_4__ btm_cb ; 
 scalar_t__ btsnd_hcic_ble_set_random_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_BleSetRandAddress(BD_ADDR rand_addr)
{
	if (rand_addr == NULL) {
		return BTM_SET_STATIC_RAND_ADDR_FAIL;
    }

    if (!(btm_cb.ble_ctr_cb.inq_var.state == BTM_BLE_STOP_SCAN || btm_cb.ble_ctr_cb.inq_var.state == BTM_BLE_STOP_ADV || btm_cb.ble_ctr_cb.inq_var.state == BTM_BLE_IDLE)) {
        BTM_TRACE_ERROR("Advertising or scaning now, can't set randaddress %d", btm_cb.ble_ctr_cb.inq_var.state);
        return BTM_SET_STATIC_RAND_ADDR_FAIL;
    }
    memcpy(btm_cb.ble_ctr_cb.addr_mgnt_cb.private_addr, rand_addr, BD_ADDR_LEN);
    memcpy(btm_cb.ble_ctr_cb.addr_mgnt_cb.static_rand_addr, rand_addr, BD_ADDR_LEN);
    //send the set random address to the controller
    if(btsnd_hcic_ble_set_random_addr(rand_addr)) {
        btm_cb.ble_ctr_cb.addr_mgnt_cb.exist_addr_bit |= BTM_BLE_GAP_ADDR_BIT_RANDOM;
        return BTM_SUCCESS;
    } else {
        return BTM_SET_STATIC_RAND_ADDR_FAIL;
    }
}