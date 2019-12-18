#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* poll_cmd_done ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/ * get_spi_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_flash_ll_get_buffer_data (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  spi_flash_ll_set_address (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_flash_ll_set_miso_bitlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_flash_ll_user_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

esp_err_t spi_flash_hal_read(spi_flash_host_driver_t *host, void *buffer, uint32_t address, uint32_t read_len)
{
    spi_dev_t *dev = get_spi_dev(host);
    //the command is already set by ``spi_flash_hal_configure_host_io_mode`` before.
    spi_flash_ll_set_address(dev, address << 8);
    spi_flash_ll_set_miso_bitlen(dev, read_len * 8);
    spi_flash_ll_user_start(dev);
    host->poll_cmd_done(host);
    spi_flash_ll_get_buffer_data(dev, buffer, read_len);
    return ESP_OK;
}