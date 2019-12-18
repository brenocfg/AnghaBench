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
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_flash_common_read_status_8b_rdsr ; 
 int /*<<< orphan*/  spi_flash_common_set_io_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  spi_flash_common_write_status_8b_wrsr ; 

esp_err_t spi_flash_chip_issi_set_io_mode(esp_flash_t *chip)
{
    /* ISSI uses bit 6 of "basic" SR as Quad Enable */
    const uint8_t BIT_QE = 1 << 6;
    return spi_flash_common_set_io_mode(chip,
                                        spi_flash_common_write_status_8b_wrsr,
                                        spi_flash_common_read_status_8b_rdsr,
                                        BIT_QE);
}