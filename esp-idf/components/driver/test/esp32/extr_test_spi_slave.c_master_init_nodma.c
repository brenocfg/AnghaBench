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
struct TYPE_5__ {int clock_speed_hz; int queue_size; int cs_ena_posttrans; int cs_ena_pretrans; int /*<<< orphan*/ * pre_cb; int /*<<< orphan*/  spics_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
struct TYPE_6__ {int quadwp_io_num; int quadhd_io_num; int /*<<< orphan*/  sclk_io_num; int /*<<< orphan*/  mosi_io_num; int /*<<< orphan*/  miso_io_num; } ;
typedef  TYPE_2__ spi_bus_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  PIN_NUM_CLK ; 
 int /*<<< orphan*/  PIN_NUM_CS ; 
 int /*<<< orphan*/  PIN_NUM_MISO ; 
 int /*<<< orphan*/  PIN_NUM_MOSI ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_SPI_HOST ; 
 scalar_t__ spi_bus_add_device (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ spi_bus_initialize (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void master_init_nodma( spi_device_handle_t* spi)
{
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=4*1000*1000,            //currently only up to 4MHz for internel connect
        .mode=0,                                //SPI mode 0
        .spics_io_num=PIN_NUM_CS,               //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
        .pre_cb=NULL,
        .cs_ena_posttrans=5,
        .cs_ena_pretrans=1,
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(TEST_SPI_HOST, &buscfg, 0);
    TEST_ASSERT(ret==ESP_OK);
    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(TEST_SPI_HOST, &devcfg, spi);
    TEST_ASSERT(ret==ESP_OK);
}