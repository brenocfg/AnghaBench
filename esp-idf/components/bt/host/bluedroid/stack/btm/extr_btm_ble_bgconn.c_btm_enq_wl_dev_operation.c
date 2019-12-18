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
struct TYPE_5__ {scalar_t__ addr_type; int /*<<< orphan*/  bd_addr; void* to_add; scalar_t__ in_use; } ;
typedef  TYPE_2__ tBTM_BLE_WL_OP ;
typedef  scalar_t__ tBLE_ADDR_TYPE ;
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {TYPE_2__* wl_op_q; } ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;
typedef  void* BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_BLE_MAX_BG_CONN_DEV_NUM ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 scalar_t__ TRUE ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_enq_wl_dev_operation(BOOLEAN to_add, BD_ADDR bd_addr, tBLE_ADDR_TYPE addr_type)
{
    tBTM_BLE_WL_OP *p_dev_op = btm_cb.ble_ctr_cb.wl_op_q;
    UINT8   i = 0;

    for (i = 0; i < BTM_BLE_MAX_BG_CONN_DEV_NUM; i ++, p_dev_op ++) {
        if (p_dev_op->in_use && p_dev_op->addr_type == addr_type && !memcmp(p_dev_op->bd_addr, bd_addr, BD_ADDR_LEN)) {
            p_dev_op->to_add = to_add;
            return;
        } else if (!p_dev_op->in_use) {
            break;
        }
    }
    if (i != BTM_BLE_MAX_BG_CONN_DEV_NUM) {
        p_dev_op->in_use = TRUE;
        p_dev_op->to_add = to_add;
        p_dev_op->addr_type = addr_type;
        memcpy(p_dev_op->bd_addr, bd_addr, BD_ADDR_LEN);
    } else {
        BTM_TRACE_ERROR("max pending WL operation reached, discard");
    }
    return;
}