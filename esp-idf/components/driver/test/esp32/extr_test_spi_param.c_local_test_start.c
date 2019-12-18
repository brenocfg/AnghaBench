#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ dup; int master_limit; int test_size; scalar_t__ slave_iomux; scalar_t__ master_iomux; int /*<<< orphan*/  slave_dma_chan; int /*<<< orphan*/  master_dma_chan; int /*<<< orphan*/  mode; int /*<<< orphan*/  slave_tv_ns; } ;
typedef  TYPE_2__ spitest_param_set_t ;
struct TYPE_17__ {int /*<<< orphan*/  data_to_send; } ;
struct TYPE_19__ {int /*<<< orphan*/  master_rxbuf; int /*<<< orphan*/ * slave_trans; TYPE_1__ slave_context; } ;
typedef  TYPE_3__ spitest_context_t ;
struct TYPE_20__ {void* spics_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_4__ spi_slave_interface_config_t ;
struct TYPE_21__ {int spics_io_num; int cs_ena_pretrans; int cs_ena_posttrans; int clock_speed_hz; int /*<<< orphan*/  flags; int /*<<< orphan*/  input_delay_ns; int /*<<< orphan*/  mode; } ;
typedef  TYPE_5__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
struct TYPE_22__ {int miso_io_num; int mosi_io_num; int sclk_io_num; int quadhd_io_num; } ;
typedef  TYPE_6__ spi_bus_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_GPIO ; 
 int /*<<< orphan*/  FUNC_SPI ; 
 scalar_t__ HALF_DUPLEX_MISO ; 
 scalar_t__ HALF_DUPLEX_MOSI ; 
 int /*<<< orphan*/  HSPICLK_OUT_IDX ; 
 int /*<<< orphan*/  HSPICS0_OUT_IDX ; 
 int /*<<< orphan*/  HSPID_OUT_IDX ; 
 int HSPI_IOMUX_PIN_NUM_CLK ; 
 void* HSPI_IOMUX_PIN_NUM_CS ; 
 int HSPI_IOMUX_PIN_NUM_MISO ; 
 int HSPI_IOMUX_PIN_NUM_MOSI ; 
 TYPE_6__ SPI_BUS_TEST_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  SPI_DEVICE_HALFDUPLEX ; 
 int /*<<< orphan*/  SPI_DEVICE_NO_DUMMY ; 
 TYPE_5__ SPI_DEVICE_TEST_DEFAULT_CONFIG () ; 
 TYPE_4__ SPI_SLAVE_TEST_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SLAVE_HOST ; 
 int /*<<< orphan*/  TEST_SPI_HOST ; 
 int /*<<< orphan*/  VSPIQ_OUT_IDX ; 
 int VSPI_IOMUX_PIN_NUM_CLK ; 
 void* VSPI_IOMUX_PIN_NUM_CS ; 
 int VSPI_IOMUX_PIN_NUM_MISO ; 
 int VSPI_IOMUX_PIN_NUM_MOSI ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  slave_pull_up (TYPE_6__*,void*) ; 
 int /*<<< orphan*/  spi_bus_add_device (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_bus_initialize (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_slave_initialize (int /*<<< orphan*/ ,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spitest_gpio_output_sel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xQueueSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void local_test_start(spi_device_handle_t *spi, int freq, const spitest_param_set_t* pset, spitest_context_t* context)
{
    //master config
    spi_bus_config_t buscfg = SPI_BUS_TEST_DEFAULT_CONFIG();
    spi_device_interface_config_t devcfg = SPI_DEVICE_TEST_DEFAULT_CONFIG();
    spi_slave_interface_config_t slvcfg = SPI_SLAVE_TEST_DEFAULT_CONFIG();
    //pin config & initialize
    //we can't have two sets of iomux pins on the same pins
    assert(!pset->master_iomux || !pset->slave_iomux);
    if (pset->slave_iomux) {
        //only in this case, use VSPI iomux pins
        buscfg.miso_io_num = VSPI_IOMUX_PIN_NUM_MISO;
        buscfg.mosi_io_num = VSPI_IOMUX_PIN_NUM_MOSI;
        buscfg.sclk_io_num = VSPI_IOMUX_PIN_NUM_CLK;
        devcfg.spics_io_num = VSPI_IOMUX_PIN_NUM_CS;
        slvcfg.spics_io_num = VSPI_IOMUX_PIN_NUM_CS;
    } else {
        buscfg.miso_io_num = HSPI_IOMUX_PIN_NUM_MISO;
        buscfg.mosi_io_num = HSPI_IOMUX_PIN_NUM_MOSI;
        buscfg.sclk_io_num = HSPI_IOMUX_PIN_NUM_CLK;
        devcfg.spics_io_num = HSPI_IOMUX_PIN_NUM_CS;
        slvcfg.spics_io_num = HSPI_IOMUX_PIN_NUM_CS;
    }
    //this does nothing, but avoid the driver from using iomux pins if required
    buscfg.quadhd_io_num = (!pset->master_iomux && !pset->slave_iomux ? VSPI_IOMUX_PIN_NUM_MISO : -1);
    devcfg.mode = pset->mode;
    const int cs_pretrans_max = 15;
    if (pset->dup == HALF_DUPLEX_MISO) {
        devcfg.cs_ena_pretrans = cs_pretrans_max;
        devcfg.flags |= SPI_DEVICE_HALFDUPLEX;
    } else if (pset->dup == HALF_DUPLEX_MOSI) {
        devcfg.cs_ena_pretrans = cs_pretrans_max;
        devcfg.flags |= SPI_DEVICE_NO_DUMMY;
    } else {
        devcfg.cs_ena_pretrans = cs_pretrans_max;
    }
    const int cs_posttrans_max = 15;
    devcfg.cs_ena_posttrans = cs_posttrans_max;
    devcfg.input_delay_ns = pset->slave_tv_ns;
    devcfg.clock_speed_hz = freq;
    if (pset->master_limit != 0 && freq > pset->master_limit) devcfg.flags |= SPI_DEVICE_NO_DUMMY;

    //slave config
    slvcfg.mode = pset->mode;

    slave_pull_up(&buscfg, slvcfg.spics_io_num);

    TEST_ESP_OK(spi_bus_initialize(TEST_SPI_HOST, &buscfg, pset->master_dma_chan));
    TEST_ESP_OK(spi_bus_add_device(TEST_SPI_HOST, &devcfg, spi));

    //slave automatically use iomux pins if pins are on VSPI_* pins
    buscfg.quadhd_io_num = -1;
    TEST_ESP_OK(spi_slave_initialize(TEST_SLAVE_HOST, &buscfg, &slvcfg, pset->slave_dma_chan));

    //initialize master and slave on the same pins break some of the output configs, fix them
    if (pset->master_iomux) {
        spitest_gpio_output_sel(buscfg.mosi_io_num, FUNC_SPI, HSPID_OUT_IDX);
        spitest_gpio_output_sel(buscfg.miso_io_num, FUNC_GPIO, VSPIQ_OUT_IDX);
        spitest_gpio_output_sel(devcfg.spics_io_num, FUNC_SPI, HSPICS0_OUT_IDX);
        spitest_gpio_output_sel(buscfg.sclk_io_num, FUNC_SPI, HSPICLK_OUT_IDX);
    } else if (pset->slave_iomux) {
        spitest_gpio_output_sel(buscfg.mosi_io_num, FUNC_GPIO, HSPID_OUT_IDX);
        spitest_gpio_output_sel(buscfg.miso_io_num, FUNC_SPI, VSPIQ_OUT_IDX);
        spitest_gpio_output_sel(devcfg.spics_io_num, FUNC_GPIO, HSPICS0_OUT_IDX);
        spitest_gpio_output_sel(buscfg.sclk_io_num, FUNC_GPIO, HSPICLK_OUT_IDX);
    } else {
        spitest_gpio_output_sel(buscfg.mosi_io_num, FUNC_GPIO, HSPID_OUT_IDX);
        spitest_gpio_output_sel(buscfg.miso_io_num, FUNC_GPIO, VSPIQ_OUT_IDX);
        spitest_gpio_output_sel(devcfg.spics_io_num, FUNC_GPIO, HSPICS0_OUT_IDX);
        spitest_gpio_output_sel(buscfg.sclk_io_num, FUNC_GPIO, HSPICLK_OUT_IDX);
    }

    //prepare slave tx data
    for (int k = 0; k < pset->test_size; k++)
        xQueueSend(context->slave_context.data_to_send, &context->slave_trans[k], portMAX_DELAY);

    //clear master receive buffer
    memset(context->master_rxbuf, 0x66, sizeof(context->master_rxbuf));

}