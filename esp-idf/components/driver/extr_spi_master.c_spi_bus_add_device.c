#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spi_trans_priv_t ;
typedef  size_t spi_host_device_t ;
typedef  int /*<<< orphan*/  spi_hal_timing_conf_t ;
struct TYPE_17__ {int half_duplex; int as_cs; int positive_cs; int no_compensate; } ;
typedef  TYPE_1__ spi_hal_context_t ;
struct TYPE_16__ {int duty_cycle_pos; } ;
struct TYPE_18__ {int id; int waiting; scalar_t__ semphr_polling; void* ret_queue; void* trans_queue; TYPE_10__ cfg; TYPE_5__* host; int /*<<< orphan*/  timing_conf; } ;
typedef  TYPE_2__ spi_device_t ;
struct TYPE_19__ {scalar_t__ spics_io_num; int cs_ena_pretrans; scalar_t__ address_bits; scalar_t__ command_bits; int flags; int duty_cycle_pos; int /*<<< orphan*/  queue_size; int /*<<< orphan*/  input_delay_ns; int /*<<< orphan*/  clock_speed_hz; } ;
typedef  TYPE_3__ spi_device_interface_config_t ;
typedef  TYPE_2__* spi_device_handle_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_20__ {int flags; int /*<<< orphan*/ * device; TYPE_1__ hal; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,size_t,int,int) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ GPIO_IS_VALID_OUTPUT_GPIO (scalar_t__) ; 
 int NO_CS ; 
 int SPICOMMON_BUSFLAG_IOMUX_PINS ; 
 int /*<<< orphan*/  SPI_CHECK (int,char*,scalar_t__) ; 
 int SPI_DEVICE_CLK_AS_CS ; 
 int SPI_DEVICE_HALFDUPLEX ; 
 int SPI_DEVICE_NO_DUMMY ; 
 int SPI_DEVICE_POSITIVE_CS ; 
 size_t SPI_HOST ; 
 int /*<<< orphan*/  SPI_TAG ; 
 size_t VSPI_HOST ; 
 scalar_t__ atomic_compare_exchange_strong (int /*<<< orphan*/ *,void**,TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_10__*,TYPE_3__ const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ spi_hal_get_clock_conf (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spicommon_cs_initialize (size_t,scalar_t__,int,int) ; 
 TYPE_5__** spihost ; 
 int /*<<< orphan*/  vQueueDelete (void*) ; 
 int /*<<< orphan*/  vSemaphoreDelete (scalar_t__) ; 
 void* xQueueCreate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xSemaphoreCreateBinary () ; 

esp_err_t spi_bus_add_device(spi_host_device_t host, const spi_device_interface_config_t *dev_config, spi_device_handle_t *handle)
{
    int freecs;
    int duty_cycle;

    SPI_CHECK(host>=SPI_HOST && host<=VSPI_HOST, "invalid host", ESP_ERR_INVALID_ARG);
    SPI_CHECK(spihost[host]!=NULL, "host not initialized", ESP_ERR_INVALID_STATE);
    SPI_CHECK(dev_config->spics_io_num < 0 || GPIO_IS_VALID_OUTPUT_GPIO(dev_config->spics_io_num), "spics pin invalid", ESP_ERR_INVALID_ARG);
    SPI_CHECK(dev_config->clock_speed_hz > 0, "invalid sclk speed", ESP_ERR_INVALID_ARG);
    for (freecs=0; freecs<NO_CS; freecs++) {
        //See if this slot is free; reserve if it is by putting a dummy pointer in the slot. We use an atomic compare&swap to make this thread-safe.
        void* null=NULL;
        if (atomic_compare_exchange_strong(&spihost[host]->device[freecs], &null, (spi_device_t *)1)) break;
    }
    SPI_CHECK(freecs!=NO_CS, "no free cs pins for host", ESP_ERR_NOT_FOUND);
#ifdef CONFIG_IDF_TARGET_ESP32
    //The hardware looks like it would support this, but actually setting cs_ena_pretrans when transferring in full
    //duplex mode does absolutely nothing on the ESP32.
    SPI_CHECK( dev_config->cs_ena_pretrans <= 1 || (dev_config->address_bits == 0 && dev_config->command_bits == 0) ||
        (dev_config->flags & SPI_DEVICE_HALFDUPLEX), "In full-duplex mode, only support cs pretrans delay = 1 and without address_bits and command_bits", ESP_ERR_INVALID_ARG);
#endif

    duty_cycle = (dev_config->duty_cycle_pos==0) ? 128 : dev_config->duty_cycle_pos;

    int freq;
    spi_hal_context_t *hal = &spihost[host]->hal;
    hal->half_duplex = dev_config->flags & SPI_DEVICE_HALFDUPLEX ? 1 : 0;
#ifdef SOC_SPI_SUPPORT_AS_CS
    hal->as_cs = dev_config->flags & SPI_DEVICE_CLK_AS_CS ? 1 : 0;
#endif
    hal->positive_cs = dev_config->flags & SPI_DEVICE_POSITIVE_CS ? 1 : 0;
    hal->no_compensate = dev_config->flags & SPI_DEVICE_NO_DUMMY ? 1 : 0;

    spi_hal_timing_conf_t temp_timing_conf;
    esp_err_t ret = spi_hal_get_clock_conf(hal, dev_config->clock_speed_hz, duty_cycle,
                                        !(spihost[host]->flags & SPICOMMON_BUSFLAG_IOMUX_PINS),
                                        dev_config->input_delay_ns, &freq,
                                        &temp_timing_conf);

    SPI_CHECK(ret==ESP_OK, "assigned clock speed not supported", ret);


    //Allocate memory for device
    spi_device_t *dev=malloc(sizeof(spi_device_t));
    if (dev==NULL) goto nomem;
    memset(dev, 0, sizeof(spi_device_t));
    atomic_store(&spihost[host]->device[freecs], dev);
    dev->id = freecs;
    dev->waiting = false;
    dev->timing_conf = temp_timing_conf;

    //Allocate queues, set defaults
    dev->trans_queue = xQueueCreate(dev_config->queue_size, sizeof(spi_trans_priv_t));
    dev->ret_queue = xQueueCreate(dev_config->queue_size, sizeof(spi_trans_priv_t));
    dev->semphr_polling = xSemaphoreCreateBinary();
    if (!dev->trans_queue || !dev->ret_queue || !dev->semphr_polling) {
        goto nomem;
    }
    dev->host=spihost[host];

    //We want to save a copy of the dev config in the dev struct.
    memcpy(&dev->cfg, dev_config, sizeof(spi_device_interface_config_t));
    dev->cfg.duty_cycle_pos = duty_cycle;
    // TODO: if we have to change the apb clock among transactions, re-calculate this each time the apb clock lock is acquired.

    //Set CS pin, CS options
    if (dev_config->spics_io_num >= 0) {
        spicommon_cs_initialize(host, dev_config->spics_io_num, freecs, !(spihost[host]->flags&SPICOMMON_BUSFLAG_IOMUX_PINS));
    }

    *handle=dev;
    ESP_LOGD(SPI_TAG, "SPI%d: New device added to CS%d, effective clock: %dkHz", host+1, freecs, freq/1000);
    return ESP_OK;

nomem:
    if (dev) {
        if (dev->trans_queue) vQueueDelete(dev->trans_queue);
        if (dev->ret_queue) vQueueDelete(dev->ret_queue);
        if (dev->semphr_polling) vSemaphoreDelete(dev->semphr_polling);
    }
    free(dev);
    return ESP_ERR_NO_MEM;
}