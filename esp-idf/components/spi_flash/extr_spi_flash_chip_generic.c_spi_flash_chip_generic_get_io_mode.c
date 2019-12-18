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
typedef  int const uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  esp_flash_io_mode_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SPI_FLASH_QOUT ; 
 scalar_t__ spi_flash_common_read_status_8b_rdsr2 (int /*<<< orphan*/ *,int const*) ; 

esp_err_t spi_flash_chip_generic_get_io_mode(esp_flash_t *chip, esp_flash_io_mode_t* out_io_mode)
{
    // On "generic" chips, this involves checking
    // bit 1 (QE) of RDSR2 (35h) result
    // (it works this way on GigaDevice & Fudan Micro chips, probably others...)
    const uint8_t BIT_QE = 1 << 1;
    uint32_t sr;
    esp_err_t ret = spi_flash_common_read_status_8b_rdsr2(chip, &sr);
    if (ret == ESP_OK) {
        *out_io_mode = ((sr & BIT_QE)? SPI_FLASH_QOUT: 0);
    }
    return ret;
}