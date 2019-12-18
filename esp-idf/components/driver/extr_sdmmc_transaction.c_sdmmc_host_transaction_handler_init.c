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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_PM_APB_FREQ_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_pm_lock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int s_is_app_cmd ; 
 int /*<<< orphan*/  s_pm_lock ; 
 int /*<<< orphan*/ * s_request_mutex ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xSemaphoreCreateMutex () ; 

esp_err_t sdmmc_host_transaction_handler_init(void)
{
    assert(s_request_mutex == NULL);
    s_request_mutex = xSemaphoreCreateMutex();
    if (!s_request_mutex) {
        return ESP_ERR_NO_MEM;
    }
    s_is_app_cmd = false;
#ifdef CONFIG_PM_ENABLE
    esp_err_t err = esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "sdmmc", &s_pm_lock);
    if (err != ESP_OK) {
        vSemaphoreDelete(s_request_mutex);
        s_request_mutex = NULL;
        return err;
    }
#endif
    return ESP_OK;
}