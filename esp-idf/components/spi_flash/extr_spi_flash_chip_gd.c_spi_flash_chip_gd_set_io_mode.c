#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  chip_id; } ;
typedef  TYPE_1__ esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 scalar_t__ WRSR_16B_REQUIRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_flash_common_read_status_16b_rdsr_rdsr2 ; 
 int /*<<< orphan*/  spi_flash_common_read_status_8b_rdsr2 ; 
 int /*<<< orphan*/  spi_flash_common_set_io_mode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  spi_flash_common_write_status_16b_wrsr ; 
 int /*<<< orphan*/  spi_flash_common_write_status_8b_wrsr2 ; 

esp_err_t spi_flash_chip_gd_set_io_mode(esp_flash_t *chip)
{
    if (WRSR_16B_REQUIRED(chip->chip_id)) {
        const uint32_t qe = 1<<9;
        return spi_flash_common_set_io_mode(chip,
                                            spi_flash_common_write_status_16b_wrsr,
                                            spi_flash_common_read_status_16b_rdsr_rdsr2,
                                            qe);
    } else {
        const uint32_t qe = 1<<1;
        return spi_flash_common_set_io_mode(chip,
                                            spi_flash_common_write_status_8b_wrsr2,
                                            spi_flash_common_read_status_8b_rdsr2,
                                            qe);
    }
}