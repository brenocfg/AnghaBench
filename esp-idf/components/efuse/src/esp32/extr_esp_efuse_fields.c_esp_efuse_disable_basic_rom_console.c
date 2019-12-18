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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_EFUSE_CONSOLE_DEBUG_DISABLE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_efuse_read_field_blob (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  esp_efuse_write_field_cnt (int /*<<< orphan*/ ,int) ; 

void esp_efuse_disable_basic_rom_console(void)
{
    uint8_t console_debug_disable = 0;
    esp_efuse_read_field_blob(ESP_EFUSE_CONSOLE_DEBUG_DISABLE, &console_debug_disable, 1);
    if (console_debug_disable == 0) {
        esp_efuse_write_field_cnt(ESP_EFUSE_CONSOLE_DEBUG_DISABLE, 1);
        ESP_EARLY_LOGI(TAG, "Disable BASIC ROM Console fallback via efuse...");
    }
}