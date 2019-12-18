#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  miso_data; int /*<<< orphan*/  mosi_data; int /*<<< orphan*/  mosi_len; int /*<<< orphan*/  miso_len; int /*<<< orphan*/  command; } ;
typedef  TYPE_1__ spi_flash_trans_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* poll_cmd_done ) (TYPE_2__*) ;int /*<<< orphan*/  (* configure_host_io_mode ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ spi_flash_host_driver_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SPI_FLASH_FASTRD ; 
 int /*<<< orphan*/ * get_spi_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  spi_flash_ll_get_buffer_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_flash_ll_set_dummy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_flash_ll_set_miso_bitlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_flash_ll_set_mosi_bitlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_flash_ll_user_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_flash_ll_write_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

esp_err_t spi_flash_hal_common_command(spi_flash_host_driver_t *host, spi_flash_trans_t *trans)
{
    host->configure_host_io_mode(host, trans->command, 0, 0, SPI_FLASH_FASTRD);

    spi_dev_t *dev = get_spi_dev(host);
    //disable dummy if no input phase
    if (trans->miso_len == 0) {
        spi_flash_ll_set_dummy(dev, 0);
    }

    spi_flash_ll_set_miso_bitlen(dev, trans->miso_len);
    spi_flash_ll_set_mosi_bitlen(dev, trans->mosi_len);

    spi_flash_ll_write_word(dev, trans->mosi_data);

    spi_flash_ll_user_start(dev);
    host->poll_cmd_done(host);
    spi_flash_ll_get_buffer_data(dev, trans->miso_data, 8);
    return ESP_OK;
}