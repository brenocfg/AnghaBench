#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int test_size; scalar_t__ dup; int /*<<< orphan*/  slave_dma_chan; int /*<<< orphan*/  mode; int /*<<< orphan*/  slave_iomux; } ;
typedef  TYPE_3__ spitest_param_set_t ;
struct TYPE_17__ {TYPE_2__* master_trans; TYPE_1__* slave_trans; } ;
typedef  TYPE_4__ spitest_context_t ;
struct TYPE_18__ {int /*<<< orphan*/  spics_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_5__ spi_slave_interface_config_t ;
struct TYPE_19__ {int /*<<< orphan*/  quadhd_io_num; int /*<<< orphan*/  sclk_io_num; int /*<<< orphan*/  mosi_io_num; int /*<<< orphan*/  miso_io_num; } ;
typedef  TYPE_6__ spi_bus_config_t ;
struct TYPE_15__ {int length; int rxlength; int /*<<< orphan*/  rx_buffer; } ;
struct TYPE_14__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ FULL_DUPLEX ; 
 scalar_t__ HALF_DUPLEX_MISO ; 
 int /*<<< orphan*/  HSPI_IOMUX_PIN_NUM_CLK ; 
 TYPE_6__ SPI_BUS_TEST_DEFAULT_CONFIG () ; 
 TYPE_5__ SPI_SLAVE_TEST_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int /*<<< orphan*/  VSPI_IOMUX_PIN_NUM_CLK ; 
 int /*<<< orphan*/  VSPI_IOMUX_PIN_NUM_CS ; 
 int /*<<< orphan*/  VSPI_IOMUX_PIN_NUM_MISO ; 
 int /*<<< orphan*/  VSPI_IOMUX_PIN_NUM_MOSI ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slave_pull_up (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_slave_initialize (int /*<<< orphan*/ ,TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timing_slave_start(int speed, const spitest_param_set_t* pset, spitest_context_t *context)
{
    //slave config
    spi_bus_config_t slv_buscfg=SPI_BUS_TEST_DEFAULT_CONFIG();
    slv_buscfg.miso_io_num = VSPI_IOMUX_PIN_NUM_MISO;
    slv_buscfg.mosi_io_num = VSPI_IOMUX_PIN_NUM_MOSI;
    slv_buscfg.sclk_io_num = VSPI_IOMUX_PIN_NUM_CLK;
    //this does nothing, but avoid the driver from using native pins
    if (!pset->slave_iomux) slv_buscfg.quadhd_io_num = HSPI_IOMUX_PIN_NUM_CLK;
    spi_slave_interface_config_t slvcfg=SPI_SLAVE_TEST_DEFAULT_CONFIG();
    slvcfg.spics_io_num = VSPI_IOMUX_PIN_NUM_CS;
    slvcfg.mode = pset->mode;
    //Enable pull-ups on SPI lines so we don't detect rogue pulses when no master is connected.
    slave_pull_up(&slv_buscfg, slvcfg.spics_io_num);

    TEST_ESP_OK(spi_slave_initialize(TEST_SLAVE_HOST, &slv_buscfg, &slvcfg, pset->slave_dma_chan));

    //prepare data for the master
    for (int i = 0; i < pset->test_size; i++) {
        if (pset->dup==FULL_DUPLEX) {
            memcpy(context->master_trans[i].rx_buffer, context->slave_trans[i].start, (context->master_trans[i].length+7)/8);
        } else if (pset->dup==HALF_DUPLEX_MISO) {
            memcpy(context->master_trans[i].rx_buffer, context->slave_trans[i].start, (context->master_trans[i].rxlength+7)/8);
        }
    }
}