#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gatt_db; } ;
typedef  TYPE_1__ simple_ble_cfg_t ;

/* Variables and functions */
 int ble_gatts_add_svcs (int /*<<< orphan*/ ) ; 
 int ble_gatts_count_cfg (int /*<<< orphan*/ ) ; 

int
gatt_svr_init(const simple_ble_cfg_t *config)
{
    int rc;
    rc = ble_gatts_count_cfg(config->gatt_db);
    if (rc != 0) {
        return rc;
    }

    rc = ble_gatts_add_svcs(config->gatt_db);
    if (rc != 0) {
        return rc;
    }

    return 0;
}