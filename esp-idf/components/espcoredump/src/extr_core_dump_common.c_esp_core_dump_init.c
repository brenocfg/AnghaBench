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
 int /*<<< orphan*/  ESP_COREDUMP_LOGI (char*) ; 
 int /*<<< orphan*/  esp_core_dump_flash_init () ; 

void esp_core_dump_init(void)
{
#if CONFIG_ESP32_ENABLE_COREDUMP_TO_FLASH
    esp_core_dump_flash_init();
#endif
#if CONFIG_ESP32_ENABLE_COREDUMP_TO_UART
    ESP_COREDUMP_LOGI("Init core dump to UART");
#endif
}