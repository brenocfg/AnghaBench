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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int FLASH_ID_MASK ; 
 int GD25LQ_PRODUCT_ID ; 
 int GD25Q_PRODUCT_ID ; 

esp_err_t spi_flash_chip_gd_probe(esp_flash_t *chip, uint32_t flash_id)
{
    /* Check manufacturer and product IDs match our desired masks */
    const uint8_t MFG_ID = 0xC8;
    if (flash_id >> 16 != MFG_ID) {
        return ESP_ERR_NOT_FOUND;
    }

    uint32_t product_id = flash_id & FLASH_ID_MASK;
    if (product_id != GD25Q_PRODUCT_ID && product_id != GD25LQ_PRODUCT_ID) {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}