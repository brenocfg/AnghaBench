#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t spi_host_device_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {TYPE_1__* dmadesc_tx; TYPE_1__* dmadesc_rx; } ;
struct TYPE_4__ {scalar_t__ dma_chan; int /*<<< orphan*/  intr; TYPE_2__ hal; int /*<<< orphan*/  pm_lock; int /*<<< orphan*/  bus_cfg; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int NO_CS ; 
 int /*<<< orphan*/  SPI_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 size_t SPI_HOST ; 
 size_t VSPI_HOST ; 
 int /*<<< orphan*/ * atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_pm_lock_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_hal_deinit (TYPE_2__*) ; 
 int /*<<< orphan*/  spicommon_bus_free_io_cfg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spicommon_dma_chan_free (scalar_t__) ; 
 int /*<<< orphan*/  spicommon_periph_free (size_t) ; 
 TYPE_1__** spihost ; 

esp_err_t spi_bus_free(spi_host_device_t host)
{
    int x;
    SPI_CHECK(host>=SPI_HOST && host<=VSPI_HOST, "invalid host", ESP_ERR_INVALID_ARG);
    SPI_CHECK(spihost[host]!=NULL, "host not in use", ESP_ERR_INVALID_STATE);
    for (x=0; x<NO_CS; x++) {
        SPI_CHECK(atomic_load(&spihost[host]->device[x])==NULL, "not all CSses freed", ESP_ERR_INVALID_STATE);
    }
    spicommon_bus_free_io_cfg(&spihost[host]->bus_cfg);

    if ( spihost[host]->dma_chan > 0 ) {
        spicommon_dma_chan_free ( spihost[host]->dma_chan );
    }
#ifdef CONFIG_PM_ENABLE
    esp_pm_lock_delete(spihost[host]->pm_lock);
#endif
    spi_hal_deinit(&spihost[host]->hal);
    free(spihost[host]->hal.dmadesc_rx);
    free(spihost[host]->hal.dmadesc_tx);

    esp_intr_free(spihost[host]->intr);
    spicommon_periph_free(host);
    free(spihost[host]);
    spihost[host]=NULL;
    return ESP_OK;
}