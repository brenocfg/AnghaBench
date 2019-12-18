#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  extra_dummy; int /*<<< orphan*/  clock_conf; int /*<<< orphan*/  cs_num; } ;
typedef  TYPE_1__ spi_flash_memspi_data_t ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SPI1 ; 
 int /*<<< orphan*/ * get_spi_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  spi_flash_ll_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_flash_ll_set_clock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_flash_ll_set_cs_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t spi_flash_hal_device_config(spi_flash_host_driver_t *host)
{
    spi_flash_memspi_data_t *drv_data = (spi_flash_memspi_data_t *)host->driver_data;
    spi_dev_t *dev = get_spi_dev(host);
    spi_flash_ll_reset(dev);
    spi_flash_ll_set_cs_pin(dev, drv_data->cs_num);
    spi_flash_ll_set_clock(dev, &drv_data->clock_conf);

    /*
     * workaround for the ROM: the ROM, as well as the OpenOCD, don't know the
     * clock registers and the dummy are modified this help the ROM to read and
     * write correctly according to the new dummy len.
     */
    if (dev == &SPI1) {
        //0 for cache, 1 for SPI1
        extern uint8_t g_rom_spiflash_dummy_len_plus[];
        g_rom_spiflash_dummy_len_plus[1] = drv_data->extra_dummy;
    }
    return ESP_OK;
}