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
struct TYPE_4__ {int queue_size; } ;
typedef  TYPE_1__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
typedef  int /*<<< orphan*/  spi_bus_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SPI_BUS_TEST_DEFAULT_CONFIG () ; 
 TYPE_1__ SPI_DEVICE_TEST_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_SPI_HOST ; 
 scalar_t__ spi_bus_add_device (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ spi_bus_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void speed_setup(spi_device_handle_t* spi, bool use_dma)
{
    esp_err_t ret;
    spi_bus_config_t buscfg=SPI_BUS_TEST_DEFAULT_CONFIG();
    spi_device_interface_config_t devcfg=SPI_DEVICE_TEST_DEFAULT_CONFIG();
    devcfg.queue_size=8;       //We want to be able to queue 7 transactions at a time

    //Initialize the SPI bus and the device to test
    ret=spi_bus_initialize(TEST_SPI_HOST, &buscfg, (use_dma?1:0));
    TEST_ASSERT(ret==ESP_OK);
    ret=spi_bus_add_device(TEST_SPI_HOST, &devcfg, spi);
    TEST_ASSERT(ret==ESP_OK);
}