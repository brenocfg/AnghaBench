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
typedef  int /*<<< orphan*/  esp_rom_spiflash_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ROM_SPIFLASH_RESULT_OK ; 

esp_rom_spiflash_result_t esp_rom_spiflash_unlock(void)
{
    return ESP_ROM_SPIFLASH_RESULT_OK;
}