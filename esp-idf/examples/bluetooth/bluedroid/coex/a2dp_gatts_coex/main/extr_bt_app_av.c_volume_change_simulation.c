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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_RC_TG_TAG ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int portTICK_RATE_MS ; 
 int s_volume ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  volume_set_by_local_host (int) ; 

__attribute__((used)) static void volume_change_simulation(void *arg)
{
    ESP_LOGI(BT_RC_TG_TAG, "start volume change simulation");

    for (;;) {
        vTaskDelay(10000 / portTICK_RATE_MS);

        uint8_t volume = (s_volume + 5) & 0x7f;
        volume_set_by_local_host(volume);
    }
}