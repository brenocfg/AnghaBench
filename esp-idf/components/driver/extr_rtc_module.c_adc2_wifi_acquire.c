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
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_TAG ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adc2_wifi_lock ; 

esp_err_t adc2_wifi_acquire(void)
{
    //lazy initialization
    //for wifi, block until acquire the lock
    _lock_acquire( &adc2_wifi_lock );
    ESP_LOGD( RTC_MODULE_TAG, "Wi-Fi takes adc2 lock." );
    return ESP_OK;
}