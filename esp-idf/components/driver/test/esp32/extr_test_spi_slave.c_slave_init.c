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
struct TYPE_5__ {int queue_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  spics_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ spi_slave_interface_config_t ;
struct TYPE_6__ {int /*<<< orphan*/  sclk_io_num; int /*<<< orphan*/  miso_io_num; int /*<<< orphan*/  mosi_io_num; } ;
typedef  TYPE_2__ spi_bus_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PULLUP_ONLY ; 
 int /*<<< orphan*/  PIN_NUM_CLK ; 
 int /*<<< orphan*/  PIN_NUM_CS ; 
 int /*<<< orphan*/  PIN_NUM_MISO ; 
 int /*<<< orphan*/  PIN_NUM_MOSI ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int /*<<< orphan*/  gpio_set_pull_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_slave_initialize (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static void slave_init(void)
{
    //Configuration for the SPI bus
    spi_bus_config_t buscfg={
        .mosi_io_num=PIN_NUM_MOSI,
        .miso_io_num=PIN_NUM_MISO,
        .sclk_io_num=PIN_NUM_CLK
    };
    //Configuration for the SPI slave interface
    spi_slave_interface_config_t slvcfg={
        .mode=0,
        .spics_io_num=PIN_NUM_CS,
        .queue_size=3,
        .flags=0,
    };
    //Enable pull-ups on SPI lines so we don't detect rogue pulses when no master is connected.
    gpio_set_pull_mode(PIN_NUM_MOSI, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_NUM_CLK, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_NUM_CS, GPIO_PULLUP_ONLY);
    //Initialize SPI slave interface
    TEST_ESP_OK( spi_slave_initialize(TEST_SLAVE_HOST, &buscfg, &slvcfg, 2) );
}