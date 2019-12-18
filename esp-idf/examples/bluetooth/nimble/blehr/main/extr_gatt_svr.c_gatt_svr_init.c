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

/* Variables and functions */
 int ble_gatts_add_svcs (int /*<<< orphan*/ ) ; 
 int ble_gatts_count_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ble_svc_gap_init () ; 
 int /*<<< orphan*/  ble_svc_gatt_init () ; 
 int /*<<< orphan*/  gatt_svr_svcs ; 

int
gatt_svr_init(void)
{
    int rc;

    ble_svc_gap_init();
    ble_svc_gatt_init();

    rc = ble_gatts_count_cfg(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    return 0;
}