#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t spi_host_device_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_2__* dmadesc_rx; TYPE_2__* dmadesc_tx; } ;
struct TYPE_7__ {scalar_t__ dma_chan; int /*<<< orphan*/  pm_lock; int /*<<< orphan*/  intr; TYPE_1__ hal; scalar_t__ ret_queue; scalar_t__ trans_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SPI_CHECK (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* VALID_HOST (size_t) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_pm_lock_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_pm_lock_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  spicommon_dma_chan_free (scalar_t__) ; 
 int /*<<< orphan*/  spicommon_periph_free (size_t) ; 
 TYPE_2__** spihost ; 
 int /*<<< orphan*/  vQueueDelete (scalar_t__) ; 

esp_err_t spi_slave_free(spi_host_device_t host)
{
    SPI_CHECK(VALID_HOST(host), "invalid host", ESP_ERR_INVALID_ARG);
    SPI_CHECK(spihost[host], "host not slave", ESP_ERR_INVALID_ARG);
    if (spihost[host]->trans_queue) vQueueDelete(spihost[host]->trans_queue);
    if (spihost[host]->ret_queue) vQueueDelete(spihost[host]->ret_queue);
    if ( spihost[host]->dma_chan > 0 ) {
        spicommon_dma_chan_free ( spihost[host]->dma_chan );
    }
    free(spihost[host]->hal.dmadesc_tx);
    free(spihost[host]->hal.dmadesc_rx);
    esp_intr_free(spihost[host]->intr);
#ifdef CONFIG_PM_ENABLE
    esp_pm_lock_release(spihost[host]->pm_lock);
    esp_pm_lock_delete(spihost[host]->pm_lock);
#endif //CONFIG_PM_ENABLE
    free(spihost[host]);
    spihost[host] = NULL;
    spicommon_periph_free(host);
    return ESP_OK;
}