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
typedef  int /*<<< orphan*/  tL2C_LCB ;
typedef  scalar_t__ tBTM_BLE_CONN_ST ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BLE_BG_CONN ; 
 scalar_t__ BLE_CONN_IDLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_enqueue_direct_conn_req (int /*<<< orphan*/ *) ; 
 scalar_t__ btm_ble_get_conn_st () ; 
 int /*<<< orphan*/  btm_ble_suspend_bg_conn () ; 
 int /*<<< orphan*/  l2cble_init_direct_conn (int /*<<< orphan*/ *) ; 

BOOLEAN l2cble_create_conn (tL2C_LCB *p_lcb)
{
    tBTM_BLE_CONN_ST     conn_st = btm_ble_get_conn_st();
    BOOLEAN         rt = FALSE;

    /* There can be only one BLE connection request outstanding at a time */
    if (conn_st == BLE_CONN_IDLE) {
        rt = l2cble_init_direct_conn(p_lcb);
    } else {
        L2CAP_TRACE_WARNING ("L2CAP - LE - cannot start new connection at conn st: %d", conn_st);

        btm_ble_enqueue_direct_conn_req(p_lcb);

        if (conn_st == BLE_BG_CONN) {
            btm_ble_suspend_bg_conn();
        }

        rt = TRUE;
    }
    return rt;
}