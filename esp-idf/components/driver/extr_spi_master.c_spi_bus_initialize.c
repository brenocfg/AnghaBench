#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spi_host_t ;
typedef  int spi_host_device_t ;
struct TYPE_11__ {int intr_flags; int flags; int /*<<< orphan*/  max_transfer_sz; } ;
typedef  TYPE_1__ spi_bus_config_t ;
typedef  int /*<<< orphan*/  lldesc_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_13__ {int dma_enabled; int dmadesc_n; TYPE_2__* dmadesc_tx; TYPE_2__* dmadesc_rx; } ;
struct TYPE_12__ {int dma_chan; int max_transfer_sz; int id; int polling; int isr_free; int bus_locked; TYPE_4__ hal; scalar_t__ pm_lock; int /*<<< orphan*/  acquire_cs; void* prev_cs; void* cur_cs; int /*<<< orphan*/  intr; int /*<<< orphan*/  flags; int /*<<< orphan*/  bus_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int ESP_INTR_FLAG_EDGE ; 
 int ESP_INTR_FLAG_HIGH ; 
 int ESP_INTR_FLAG_INTRDISABLED ; 
 int ESP_INTR_FLAG_IRAM ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_PM_APB_FREQ_MAX ; 
 int LLDESC_MAX_NUM_PER_DESC ; 
 int /*<<< orphan*/  MALLOC_CAP_DMA ; 
 void* NO_CS ; 
 int SOC_SPI_MAXIMUM_BUFFER_SIZE ; 
 int SPICOMMON_BUSFLAG_MASTER ; 
 int /*<<< orphan*/  SPI_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int SPI_HOST ; 
 int VSPI_HOST ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ esp_intr_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_pm_lock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  esp_pm_lock_delete (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 void* heap_caps_malloc (int,int /*<<< orphan*/ ) ; 
 int lldesc_get_required_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_hal_deinit (TYPE_4__*) ; 
 int /*<<< orphan*/  spi_hal_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  spi_intr ; 
 scalar_t__ spicommon_bus_initialize_io (int,TYPE_1__ const*,int,int,int /*<<< orphan*/ *) ; 
 int spicommon_dma_chan_claim (int) ; 
 int /*<<< orphan*/  spicommon_dma_chan_free (int) ; 
 int /*<<< orphan*/  spicommon_irqsource_for_host (int) ; 
 int spicommon_periph_claim (int,char*) ; 
 int /*<<< orphan*/  spicommon_periph_free (int) ; 
 TYPE_2__** spihost ; 

esp_err_t spi_bus_initialize(spi_host_device_t host, const spi_bus_config_t *bus_config, int dma_chan)
{
    bool spi_chan_claimed, dma_chan_claimed;
    esp_err_t ret = ESP_OK;
    esp_err_t err;
    /* ToDo: remove this when we have flash operations cooperating with this */
    SPI_CHECK(host!=SPI_HOST, "SPI1 is not supported", ESP_ERR_NOT_SUPPORTED);

    SPI_CHECK(host>=SPI_HOST && host<=VSPI_HOST, "invalid host", ESP_ERR_INVALID_ARG);
#ifdef CONFIG_IDF_TARGET_ESP32
    SPI_CHECK( dma_chan >= 0 && dma_chan <= 2, "invalid dma channel", ESP_ERR_INVALID_ARG );
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SPI_CHECK( dma_chan == 0 || dma_chan == host, "invalid dma channel", ESP_ERR_INVALID_ARG );
#endif
    SPI_CHECK((bus_config->intr_flags & (ESP_INTR_FLAG_HIGH|ESP_INTR_FLAG_EDGE|ESP_INTR_FLAG_INTRDISABLED))==0, "intr flag not allowed", ESP_ERR_INVALID_ARG);
#ifndef CONFIG_SPI_MASTER_ISR_IN_IRAM
    SPI_CHECK((bus_config->intr_flags & ESP_INTR_FLAG_IRAM)==0, "ESP_INTR_FLAG_IRAM should be disabled when CONFIG_SPI_MASTER_ISR_IN_IRAM is not set.", ESP_ERR_INVALID_ARG);
#endif

    spi_chan_claimed=spicommon_periph_claim(host, "spi master");
    SPI_CHECK(spi_chan_claimed, "host already in use", ESP_ERR_INVALID_STATE);

    if ( dma_chan != 0 ) {
        dma_chan_claimed=spicommon_dma_chan_claim(dma_chan);
        if ( !dma_chan_claimed ) {
            spicommon_periph_free( host );
            SPI_CHECK(false, "dma channel already in use", ESP_ERR_INVALID_STATE);
        }
    }

    spihost[host]=malloc(sizeof(spi_host_t));
    if (spihost[host]==NULL) {
        ret = ESP_ERR_NO_MEM;
        goto cleanup;
    }
    memset(spihost[host], 0, sizeof(spi_host_t));
    memcpy( &spihost[host]->bus_cfg, bus_config, sizeof(spi_bus_config_t));

#ifdef CONFIG_PM_ENABLE
    err = esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "spi_master",
            &spihost[host]->pm_lock);
    if (err != ESP_OK) {
        ret = err;
        goto cleanup;
    }
#endif //CONFIG_PM_ENABLE

    err = spicommon_bus_initialize_io(host, bus_config, dma_chan, SPICOMMON_BUSFLAG_MASTER|bus_config->flags, &spihost[host]->flags);
    if (err != ESP_OK) {
        ret = err;
        goto cleanup;
    }
    int dma_desc_ct=0;
    spihost[host]->dma_chan=dma_chan;
    if (dma_chan == 0) {
        spihost[host]->max_transfer_sz = SOC_SPI_MAXIMUM_BUFFER_SIZE;
    } else {
        //See how many dma descriptors we need and allocate them
        dma_desc_ct=lldesc_get_required_num(bus_config->max_transfer_sz);
        if (dma_desc_ct==0) dma_desc_ct = 1; //default to 4k when max is not given
        spihost[host]->max_transfer_sz = dma_desc_ct*LLDESC_MAX_NUM_PER_DESC;
    }

    int flags = bus_config->intr_flags | ESP_INTR_FLAG_INTRDISABLED;
    err = esp_intr_alloc(spicommon_irqsource_for_host(host), flags, spi_intr, (void*)spihost[host], &spihost[host]->intr);
    if (err != ESP_OK) {
        ret = err;
        goto cleanup;
    }
    spihost[host]->id = host;

    spihost[host]->cur_cs = NO_CS;
    spihost[host]->prev_cs = NO_CS;
    atomic_store(&spihost[host]->acquire_cs, NO_CS);
    spihost[host]->polling = false;
    spihost[host]->isr_free = true;
    spihost[host]->bus_locked = false;

    spi_hal_init(&spihost[host]->hal, host);
    spihost[host]->hal.dma_enabled = (dma_chan!=0);
    if (dma_desc_ct) {
        spihost[host]->hal.dmadesc_tx=heap_caps_malloc(sizeof(lldesc_t) * dma_desc_ct, MALLOC_CAP_DMA);
        spihost[host]->hal.dmadesc_rx=heap_caps_malloc(sizeof(lldesc_t) * dma_desc_ct, MALLOC_CAP_DMA);
        if (!spihost[host]->hal.dmadesc_tx || !spihost[host]->hal.dmadesc_rx) {
            ret = ESP_ERR_NO_MEM;
            goto cleanup;
        }
    }
    spihost[host]->hal.dmadesc_n = dma_desc_ct;
    return ESP_OK;

cleanup:
    if (spihost[host]) {
        spi_hal_deinit(&spihost[host]->hal);
#ifdef CONFIG_PM_ENABLE
        if (spihost[host]->pm_lock) {
            esp_pm_lock_delete(spihost[host]->pm_lock);
        }
#endif
        free(spihost[host]->hal.dmadesc_rx);
        free(spihost[host]->hal.dmadesc_tx);
    }
    free(spihost[host]);
    spihost[host] = NULL;
    spicommon_periph_free(host);
    if (dma_chan != 0) spicommon_dma_chan_free(dma_chan);
    return ret;
}