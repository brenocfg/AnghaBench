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
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ADDR_UNKNOWN_TYPE ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  L2CAP_ATT_CID ; 
 int /*<<< orphan*/  L2CA_ConnectFixedChnl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_ble_initiate_select_conn(BD_ADDR bda)
{
    BTM_TRACE_EVENT ("btm_ble_initiate_select_conn");

    /* use direct connection procedure to initiate connection */
    if (!L2CA_ConnectFixedChnl(L2CAP_ATT_CID, bda, BLE_ADDR_UNKNOWN_TYPE)) {
        BTM_TRACE_ERROR("btm_ble_initiate_select_conn failed");
    }
}