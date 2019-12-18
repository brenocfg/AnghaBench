#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  store_status_cb; int /*<<< orphan*/  sync_cb; int /*<<< orphan*/  reset_cb; } ;

/* Variables and functions */
 TYPE_1__ ble_hs_cfg ; 
 int /*<<< orphan*/  ble_store_util_status_rr ; 
 int /*<<< orphan*/  blemesh_on_reset ; 
 int /*<<< orphan*/  blemesh_on_sync ; 
 int /*<<< orphan*/  health_pub_init () ; 
 int /*<<< orphan*/  nimble_port_freertos_deinit () ; 
 int /*<<< orphan*/  nimble_port_run () ; 

void blemesh_host_task(void *param)
{
    ble_hs_cfg.reset_cb = blemesh_on_reset;
    ble_hs_cfg.sync_cb = blemesh_on_sync;
    ble_hs_cfg.store_status_cb = ble_store_util_status_rr;

    health_pub_init();
    nimble_port_run();
    nimble_port_freertos_deinit();
}