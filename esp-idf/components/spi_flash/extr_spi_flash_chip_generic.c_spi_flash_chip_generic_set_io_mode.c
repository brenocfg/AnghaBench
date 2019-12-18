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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_flash_common_read_status_16b_rdsr_rdsr2 ; 
 int /*<<< orphan*/  spi_flash_common_set_io_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  spi_flash_common_write_status_16b_wrsr ; 

esp_err_t spi_flash_chip_generic_set_io_mode(esp_flash_t *chip)
{
    // On "generic" chips, this involves checking
    // bit 9 (QE) of RDSR (05h) result
    const uint32_t BIT_QE = 1 << 9;
    return spi_flash_common_set_io_mode(chip,
                                        spi_flash_common_write_status_16b_wrsr,
                                        spi_flash_common_read_status_16b_rdsr_rdsr2,
                                        BIT_QE);
}