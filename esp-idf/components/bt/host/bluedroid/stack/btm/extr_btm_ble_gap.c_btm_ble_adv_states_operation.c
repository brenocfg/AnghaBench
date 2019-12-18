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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  (* BTM_TOPOLOGY_FUNC_PTR ) (int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
#define  BTM_BLE_CONNECT_DIR_EVT 132 
#define  BTM_BLE_CONNECT_EVT 131 
#define  BTM_BLE_CONNECT_LO_DUTY_DIR_EVT 130 
#define  BTM_BLE_DISCOVER_EVT 129 
#define  BTM_BLE_NON_CONNECT_EVT 128 
 int /*<<< orphan*/  BTM_BLE_STATE_CONN_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_HI_DUTY_DIR_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_LO_DUTY_DIR_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_NON_CONN_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_SCAN_ADV_BIT ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN btm_ble_adv_states_operation(BTM_TOPOLOGY_FUNC_PTR *p_handler, UINT8 adv_evt)
{
    BOOLEAN rt = FALSE;

    switch (adv_evt) {
    case BTM_BLE_CONNECT_EVT:
        rt  = (*p_handler)(BTM_BLE_STATE_CONN_ADV_BIT);
        break;

    case  BTM_BLE_NON_CONNECT_EVT:
        rt  = (*p_handler) (BTM_BLE_STATE_NON_CONN_ADV_BIT);
        break;
    case BTM_BLE_CONNECT_DIR_EVT:
        rt  =  (*p_handler) (BTM_BLE_STATE_HI_DUTY_DIR_ADV_BIT);
        break;

    case BTM_BLE_DISCOVER_EVT:
        rt  =  (*p_handler) (BTM_BLE_STATE_SCAN_ADV_BIT);
        break;

    case BTM_BLE_CONNECT_LO_DUTY_DIR_EVT:
        rt = (*p_handler) (BTM_BLE_STATE_LO_DUTY_DIR_ADV_BIT);
        break;

    default:
        BTM_TRACE_ERROR("unknown adv event : %d", adv_evt);
        break;
    }

    return rt;
}