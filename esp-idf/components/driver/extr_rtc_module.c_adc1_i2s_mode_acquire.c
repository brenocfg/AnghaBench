#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_9__ {int sar1_dig_force; } ;
struct TYPE_8__ {void* force_xpd_sar; } ;
struct TYPE_7__ {int sar1_dig_force; } ;
struct TYPE_6__ {void* force_xpd_sar; } ;
struct TYPE_10__ {TYPE_4__ sar_meas1_mux; TYPE_3__ sar_power_xpd_sar; TYPE_2__ sar_read_ctrl; TYPE_1__ sar_meas_wait2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_TAG ; 
 TYPE_5__ SENS ; 
 void* SENS_FORCE_XPD_SAR_PU ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adc1_i2s_lock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t adc1_i2s_mode_acquire(void)
{
    //lazy initialization
    //for i2s, block until acquire the lock
    _lock_acquire( &adc1_i2s_lock );
    ESP_LOGD( RTC_MODULE_TAG, "i2s mode takes adc1 lock." );
    portENTER_CRITICAL(&rtc_spinlock);
#if CONFIG_IDF_TARGET_ESP32
    SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
    //switch SARADC into DIG channel
    SENS.sar_read_ctrl.sar1_dig_force = 1;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    SENS.sar_power_xpd_sar.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
    //switch SARADC into DIG channel
    SENS.sar_meas1_mux.sar1_dig_force = 1;
#endif
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}