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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  nimble_port_freertos_deinit () ; 
 int /*<<< orphan*/  nimble_port_run () ; 

void
nimble_host_task(void *param)
{
    /* This function will return only when nimble_port_stop() is executed */
    ESP_LOGI(TAG, "BLE Host Task Started");
    nimble_port_run();

    nimble_port_freertos_deinit();
}