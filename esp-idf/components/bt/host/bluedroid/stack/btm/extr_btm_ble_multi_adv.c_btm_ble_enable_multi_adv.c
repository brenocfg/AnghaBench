#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int UINT8 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BTM_BLE_MULTI_ADV_ENB ; 
 int BTM_BLE_MULTI_ADV_ENB_LEN ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int,int) ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_MULTI_ADV_OCF ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 int /*<<< orphan*/  btm_ble_multi_adv_enq_op_q (int,int,int) ; 
 int /*<<< orphan*/  btm_ble_multi_adv_vsc_cmpl_cback ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS btm_ble_enable_multi_adv (BOOLEAN enable, UINT8 inst_id, UINT8 cb_evt)
{
    UINT8           param[BTM_BLE_MULTI_ADV_ENB_LEN], *pp;
    UINT8           enb = enable ? 1 : 0;
    tBTM_STATUS     rt;

    pp = param;
    memset(param, 0, BTM_BLE_MULTI_ADV_ENB_LEN);

    UINT8_TO_STREAM (pp, BTM_BLE_MULTI_ADV_ENB);
    UINT8_TO_STREAM (pp, enb);
    UINT8_TO_STREAM (pp, inst_id);

    BTM_TRACE_EVENT (" btm_ble_enable_multi_adv: enb %d, Inst ID %d", enb, inst_id);

    if ((rt = BTM_VendorSpecificCommand (HCI_BLE_MULTI_ADV_OCF,
                                         BTM_BLE_MULTI_ADV_ENB_LEN,
                                         param,
                                         btm_ble_multi_adv_vsc_cmpl_cback))
            == BTM_CMD_STARTED) {
        btm_ble_multi_adv_enq_op_q(BTM_BLE_MULTI_ADV_ENB, inst_id, cb_evt);
    }
    return rt;
}