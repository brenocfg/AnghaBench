#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ device_id; } ;

/* Variables and functions */
 scalar_t__ const EFUSE_SPICONFIG_SPI_DEFAULTS ; 
 int /*<<< orphan*/  FLASH_CS_IO ; 
 scalar_t__ FLASH_ID_GD25LQ32C ; 
 int /*<<< orphan*/  FLASH_SPID_IO ; 
 int /*<<< orphan*/  FLASH_SPIHD_IO ; 
 int /*<<< orphan*/  FLASH_SPIQ_IO ; 
 int /*<<< orphan*/  FLASH_SPIWP_IO ; 
 int /*<<< orphan*/  FUNC_SPICLK_SPICLK ; 
 int /*<<< orphan*/  FUN_DRV ; 
 int /*<<< orphan*/  FUN_DRV_S ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SPICLK_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SPICS0_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SPID_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SPIHD_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SPIQ_U ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_SPIWP_U ; 
 int /*<<< orphan*/  PIN_FUNC_GPIO ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPICS0_OUT_IDX ; 
 int /*<<< orphan*/  SPID_IN_IDX ; 
 int /*<<< orphan*/  SPID_OUT_IDX ; 
 int /*<<< orphan*/  SPIHD_IN_IDX ; 
 int /*<<< orphan*/  SPIHD_OUT_IDX ; 
 int /*<<< orphan*/  SPIQ_IN_IDX ; 
 int /*<<< orphan*/  SPIQ_OUT_IDX ; 
 int /*<<< orphan*/  SPIWP_IN_IDX ; 
 int /*<<< orphan*/  SPIWP_OUT_IDX ; 
 scalar_t__ ets_efuse_get_spiconfig () ; 
 TYPE_1__ g_rom_flashchip ; 
 int /*<<< orphan*/  gpio_matrix_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_matrix_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bootloader_configure_spi_pins(int drv)
{
    const uint32_t spiconfig = ets_efuse_get_spiconfig();
    if (spiconfig == EFUSE_SPICONFIG_SPI_DEFAULTS) {
        gpio_matrix_out(FLASH_CS_IO, SPICS0_OUT_IDX, 0, 0);
        gpio_matrix_out(FLASH_SPIQ_IO, SPIQ_OUT_IDX, 0, 0);
        gpio_matrix_in(FLASH_SPIQ_IO, SPIQ_IN_IDX, 0);
        gpio_matrix_out(FLASH_SPID_IO, SPID_OUT_IDX, 0, 0);
        gpio_matrix_in(FLASH_SPID_IO, SPID_IN_IDX, 0);
        gpio_matrix_out(FLASH_SPIWP_IO, SPIWP_OUT_IDX, 0, 0);
        gpio_matrix_in(FLASH_SPIWP_IO, SPIWP_IN_IDX, 0);
        gpio_matrix_out(FLASH_SPIHD_IO, SPIHD_OUT_IDX, 0, 0);
        gpio_matrix_in(FLASH_SPIHD_IO, SPIHD_IN_IDX, 0);
        //select pin function gpio
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_SPIHD_U, PIN_FUNC_GPIO);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_SPIWP_U, PIN_FUNC_GPIO);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_SPICS0_U, PIN_FUNC_GPIO);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_SPIQ_U, PIN_FUNC_GPIO);
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_SPID_U, PIN_FUNC_GPIO);
        // flash clock signal should come from IO MUX.
        // set drive ability for clock
        PIN_FUNC_SELECT(PERIPHS_IO_MUX_SPICLK_U, FUNC_SPICLK_SPICLK);
        SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPICLK_U, FUN_DRV, drv, FUN_DRV_S);

#if CONFIG_SPIRAM_TYPE_ESPPSRAM32 || CONFIG_SPIRAM_TYPE_ESPPSRAM64
        uint32_t flash_id = g_rom_flashchip.device_id;
        if (flash_id == FLASH_ID_GD25LQ32C) {
            // Set drive ability for 1.8v flash in 80Mhz.
            SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPIHD_U, FUN_DRV, 3, FUN_DRV_S);
            SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPIWP_U, FUN_DRV, 3, FUN_DRV_S);
            SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPICS0_U, FUN_DRV, 3, FUN_DRV_S);
            SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPICLK_U, FUN_DRV, 3, FUN_DRV_S);
            SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPIQ_U, FUN_DRV, 3, FUN_DRV_S);
            SET_PERI_REG_BITS(PERIPHS_IO_MUX_SPID_U, FUN_DRV, 3, FUN_DRV_S);
        }
#endif
    }
}