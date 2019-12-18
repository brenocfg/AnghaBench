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
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int ble_hs_id_infer_auto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ble_hs_util_ensure_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  own_addr_type ; 
 int /*<<< orphan*/  simple_ble_advertise () ; 

__attribute__((used)) static void
simple_ble_on_sync(void)
{
    int rc;

    rc = ble_hs_util_ensure_addr(0);
    if (rc != 0) {
        ESP_LOGE(TAG, "Error loading address");
        return;
    }

    /* Figure out address to use while advertising (no privacy for now) */
    rc = ble_hs_id_infer_auto(0, &own_addr_type);
    if (rc != 0) {
        ESP_LOGE(TAG, "error determining address type; rc=%d\n", rc);
        return;
    }

    /* Begin advertising. */
    simple_ble_advertise();
}