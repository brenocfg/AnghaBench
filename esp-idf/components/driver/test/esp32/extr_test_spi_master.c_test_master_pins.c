#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int spics_io_num; } ;
typedef  TYPE_1__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
struct TYPE_8__ {int mosi_io_num; int miso_io_num; int sclk_io_num; } ;
typedef  TYPE_2__ spi_bus_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 TYPE_2__ SPI_BUS_TEST_DEFAULT_CONFIG () ; 
 TYPE_1__ SPI_DEVICE_TEST_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TEST_SPI_HOST ; 
 int /*<<< orphan*/  master_free_device_bus (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_bus_add_device (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_bus_free (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_bus_initialize (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static esp_err_t test_master_pins(int mosi, int miso, int sclk, int cs)
{
    esp_err_t ret;
    spi_bus_config_t cfg = SPI_BUS_TEST_DEFAULT_CONFIG();
    cfg.mosi_io_num = mosi;
    cfg.miso_io_num = miso;
    cfg.sclk_io_num = sclk;

    spi_device_interface_config_t master_cfg = SPI_DEVICE_TEST_DEFAULT_CONFIG();
    master_cfg.spics_io_num = cs;

    ret = spi_bus_initialize(TEST_SPI_HOST, &cfg, 1);
    if (ret != ESP_OK) return ret;

    spi_device_handle_t spi;
    ret = spi_bus_add_device(TEST_SPI_HOST, &master_cfg, &spi);
    if (ret != ESP_OK) {
        spi_bus_free(TEST_SPI_HOST);
        return ret;
    }

    master_free_device_bus(spi);
    return ESP_OK;
}