#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__ sar1_dig_force; } ;
struct TYPE_4__ {scalar_t__ sar1_dig_force; } ;
struct TYPE_6__ {TYPE_2__ sar_meas1_mux; TYPE_1__ sar_read_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_TAG ; 
 TYPE_3__ SENS ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adc1_i2s_lock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t adc1_adc_mode_acquire(void)
{
    //lazy initialization
    //for adc1, block until acquire the lock
    _lock_acquire( &adc1_i2s_lock );
    ESP_LOGD( RTC_MODULE_TAG, "adc mode takes adc1 lock." );
    portENTER_CRITICAL(&rtc_spinlock);
    // for now the WiFi would use ADC2 and set xpd_sar force on.
    // so we can not reset xpd_sar to fsm mode directly.
    // We should handle this after the synchronization mechanism is established.

    //switch SARADC into RTC channel
#if CONFIG_IDF_TARGET_ESP32
    SENS.sar_read_ctrl.sar1_dig_force = 0;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SENS.sar_meas1_mux.sar1_dig_force = 0;
#endif
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}