#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  PERIPH_SDMMC_MODULE ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  periph_module_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s_event_queue ; 
 int /*<<< orphan*/ * s_intr_handle ; 
 int /*<<< orphan*/ * s_io_intr_event ; 
 int /*<<< orphan*/  sdmmc_host_input_clk_disable () ; 
 int /*<<< orphan*/  sdmmc_host_transaction_handler_deinit () ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 

esp_err_t sdmmc_host_deinit(void)
{
    if (!s_intr_handle) {
        return ESP_ERR_INVALID_STATE;
    }
    esp_intr_free(s_intr_handle);
    s_intr_handle = NULL;
    vQueueDelete(s_event_queue);
    s_event_queue = NULL;
    vQueueDelete(s_io_intr_event);
    s_io_intr_event = NULL;
    sdmmc_host_input_clk_disable();
    sdmmc_host_transaction_handler_deinit();
    periph_module_disable(PERIPH_SDMMC_MODULE);
    return ESP_OK;
}