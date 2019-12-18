#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int wakeup_triggers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int RTC_EXT0_TRIG_EN ; 
 int RTC_ULP_TRIG_EN ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__ s_config ; 

esp_err_t esp_sleep_enable_ulp_wakeup(void)
{
#ifdef CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_CURRENT
    return ESP_ERR_NOT_SUPPORTED;
#endif
#ifdef CONFIG_ESP32_ULP_COPROC_ENABLED
    if(s_config.wakeup_triggers & RTC_EXT0_TRIG_EN) {
        ESP_LOGE(TAG, "Conflicting wake-up trigger: ext0");
        return ESP_ERR_INVALID_STATE;
    }
    s_config.wakeup_triggers |= RTC_ULP_TRIG_EN;
    return ESP_OK;
#else
    return ESP_ERR_INVALID_STATE;
#endif
}