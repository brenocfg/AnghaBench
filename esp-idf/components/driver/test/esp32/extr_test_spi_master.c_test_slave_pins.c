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
typedef  TYPE_1__ spi_slave_interface_config_t ;
struct TYPE_8__ {int mosi_io_num; int miso_io_num; int sclk_io_num; } ;
typedef  TYPE_2__ spi_bus_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 TYPE_2__ SPI_BUS_TEST_DEFAULT_CONFIG () ; 
 TYPE_1__ SPI_SLAVE_TEST_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int /*<<< orphan*/  spi_slave_free (int /*<<< orphan*/ ) ; 
 scalar_t__ spi_slave_initialize (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static esp_err_t test_slave_pins(int mosi, int miso, int sclk, int cs)
{
    esp_err_t ret;
    spi_bus_config_t cfg = SPI_BUS_TEST_DEFAULT_CONFIG();
    cfg.mosi_io_num = mosi;
    cfg.miso_io_num = miso;
    cfg.sclk_io_num = sclk;

    spi_slave_interface_config_t slave_cfg = SPI_SLAVE_TEST_DEFAULT_CONFIG();
    slave_cfg.spics_io_num = cs;

    ret = spi_slave_initialize(TEST_SLAVE_HOST, &cfg, &slave_cfg, 1);
    if (ret != ESP_OK) return ret;

    spi_slave_free(TEST_SLAVE_HOST);
    return ESP_OK;
}