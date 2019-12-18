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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_MODULE_TAG ; 
 int /*<<< orphan*/  _lock_release (scalar_t__*) ; 
 scalar_t__ adc2_wifi_lock ; 

esp_err_t adc2_wifi_release(void)
{
    RTC_MODULE_CHECK((uint32_t*)adc2_wifi_lock != NULL, "wifi release called before acquire", ESP_ERR_INVALID_STATE );

    _lock_release( &adc2_wifi_lock );
    ESP_LOGD( RTC_MODULE_TAG, "Wi-Fi returns adc2 lock." );
    return ESP_OK;
}