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
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_update_link_topology_mask (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cble_advertiser_conn_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cble_scanner_conn_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2cble_conn_comp(UINT16 handle, UINT8 role, BD_ADDR bda, tBLE_ADDR_TYPE type,
                      UINT16 conn_interval, UINT16 conn_latency, UINT16 conn_timeout)
{
    btm_ble_update_link_topology_mask(role, TRUE);

    if (role == HCI_ROLE_MASTER) {
        l2cble_scanner_conn_comp(handle, bda, type, conn_interval, conn_latency, conn_timeout);
    } else {
        l2cble_advertiser_conn_comp(handle, bda, type, conn_interval, conn_latency, conn_timeout);
    }
}