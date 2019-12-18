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
typedef  int uint32_t ;
struct TYPE_3__ {int chip_id; } ;
typedef  TYPE_1__ esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_FLASH_UNSUPPORTED_CHIP ; 
 int /*<<< orphan*/  ESP_OK ; 

esp_err_t spi_flash_chip_generic_detect_size(esp_flash_t *chip, uint32_t *size)
{
    uint32_t id = chip->chip_id;
    *size = 0;

    /* Can't detect size unless the high byte of the product ID matches the same convention, which is usually 0x40 or
     * 0xC0 or similar. */
    if ((id & 0x0F00) != 0) {
        return ESP_ERR_FLASH_UNSUPPORTED_CHIP;
    }

    *size = 1 << (id & 0xFF);
    return ESP_OK;
}