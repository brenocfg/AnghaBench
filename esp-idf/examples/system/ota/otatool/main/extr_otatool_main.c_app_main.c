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
struct TYPE_3__ {int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* esp_ota_get_running_partition () ; 

void app_main(void)
{
    ESP_LOGI(TAG, "OTA Tool Example");

    const esp_partition_t *running = esp_ota_get_running_partition();

    // Display the running partition
    ESP_LOGI(TAG, "Running partition: %s", running->label);

    ESP_LOGI(TAG, "Example end");
}