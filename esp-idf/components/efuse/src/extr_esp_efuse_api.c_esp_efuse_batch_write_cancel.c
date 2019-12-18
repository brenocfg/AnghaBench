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
 int /*<<< orphan*/  EFUSE_LOCK_RELEASE () ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_efuse_utility_reset () ; 
 int s_batch_writing_mode ; 

esp_err_t esp_efuse_batch_write_cancel(void)
{
    if (s_batch_writing_mode == true) {
        s_batch_writing_mode = false;
        esp_efuse_utility_reset();
        ESP_LOGI(TAG, "Batch mode of writing fields is disabled");
        EFUSE_LOCK_RELEASE();
        return ESP_OK;
    } else {
        return ESP_ERR_INVALID_STATE;
    }
}