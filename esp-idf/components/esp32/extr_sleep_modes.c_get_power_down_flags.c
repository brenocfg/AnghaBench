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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {size_t* pd_options; int wakeup_triggers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 size_t ESP_PD_DOMAIN_RTC_FAST_MEM ; 
 size_t ESP_PD_DOMAIN_RTC_PERIPH ; 
 size_t ESP_PD_DOMAIN_RTC_SLOW_MEM ; 
 size_t ESP_PD_DOMAIN_XTAL ; 
 size_t ESP_PD_OPTION_AUTO ; 
 void* ESP_PD_OPTION_OFF ; 
 void* ESP_PD_OPTION_ON ; 
 int RTC_EXT0_TRIG_EN ; 
 int RTC_GPIO_TRIG_EN ; 
 int /*<<< orphan*/  RTC_SLEEP_PD_RTC_FAST_MEM ; 
 int /*<<< orphan*/  RTC_SLEEP_PD_RTC_PERIPH ; 
 int /*<<< orphan*/  RTC_SLEEP_PD_RTC_SLOW_MEM ; 
 int /*<<< orphan*/  RTC_SLEEP_PD_XTAL ; 
 int RTC_TOUCH_TRIG_EN ; 
 int RTC_ULP_TRIG_EN ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__ s_config ; 

__attribute__((used)) static uint32_t get_power_down_flags(void)
{
    // Where needed, convert AUTO options to ON. Later interpret AUTO as OFF.

    // RTC_SLOW_MEM is needed for the ULP, so keep RTC_SLOW_MEM powered up if ULP
    // is used and RTC_SLOW_MEM is Auto.
    // If there is any data placed into .rtc.data or .rtc.bss segments, and
    // RTC_SLOW_MEM is Auto, keep it powered up as well.

    // Labels are defined in the linker script, see esp32.ld.
    extern int _rtc_slow_length;

    if ((s_config.pd_options[ESP_PD_DOMAIN_RTC_SLOW_MEM] == ESP_PD_OPTION_AUTO) &&
            ((size_t) &_rtc_slow_length > 0 ||
             (s_config.wakeup_triggers & RTC_ULP_TRIG_EN))) {
        s_config.pd_options[ESP_PD_DOMAIN_RTC_SLOW_MEM] = ESP_PD_OPTION_ON;
    }

    // RTC_FAST_MEM is needed for deep sleep stub.
    // If RTC_FAST_MEM is Auto, keep it powered on, so that deep sleep stub
    // can run.
    // In the new chip revision, deep sleep stub will be optional,
    // and this can be changed.
    if (s_config.pd_options[ESP_PD_DOMAIN_RTC_FAST_MEM] == ESP_PD_OPTION_AUTO) {
        s_config.pd_options[ESP_PD_DOMAIN_RTC_FAST_MEM] = ESP_PD_OPTION_ON;
    }

    // RTC_PERIPH is needed for EXT0 wakeup and GPIO wakeup.
    // If RTC_PERIPH is auto, and EXT0/GPIO aren't enabled, power down RTC_PERIPH.
    if (s_config.pd_options[ESP_PD_DOMAIN_RTC_PERIPH] == ESP_PD_OPTION_AUTO) {
        if (s_config.wakeup_triggers & (RTC_EXT0_TRIG_EN | RTC_GPIO_TRIG_EN)) {
            s_config.pd_options[ESP_PD_DOMAIN_RTC_PERIPH] = ESP_PD_OPTION_ON;
        } else if (s_config.wakeup_triggers & (RTC_TOUCH_TRIG_EN | RTC_ULP_TRIG_EN)) {
            // In both rev. 0 and rev. 1 of ESP32, forcing power up of RTC_PERIPH
            // prevents ULP timer and touch FSMs from working correctly.
            s_config.pd_options[ESP_PD_DOMAIN_RTC_PERIPH] = ESP_PD_OPTION_OFF;
        }
    }

    if (s_config.pd_options[ESP_PD_DOMAIN_XTAL] == ESP_PD_OPTION_AUTO) {
        s_config.pd_options[ESP_PD_DOMAIN_XTAL] = ESP_PD_OPTION_OFF;
    }

    const char* option_str[] = {"OFF", "ON", "AUTO(OFF)" /* Auto works as OFF */};
    ESP_LOGD(TAG, "RTC_PERIPH: %s, RTC_SLOW_MEM: %s, RTC_FAST_MEM: %s",
            option_str[s_config.pd_options[ESP_PD_DOMAIN_RTC_PERIPH]],
            option_str[s_config.pd_options[ESP_PD_DOMAIN_RTC_SLOW_MEM]],
            option_str[s_config.pd_options[ESP_PD_DOMAIN_RTC_FAST_MEM]]);

    // Prepare flags based on the selected options
    uint32_t pd_flags = 0;
    if (s_config.pd_options[ESP_PD_DOMAIN_RTC_FAST_MEM] != ESP_PD_OPTION_ON) {
        pd_flags |= RTC_SLEEP_PD_RTC_FAST_MEM;
    }
    if (s_config.pd_options[ESP_PD_DOMAIN_RTC_SLOW_MEM] != ESP_PD_OPTION_ON) {
        pd_flags |= RTC_SLEEP_PD_RTC_SLOW_MEM;
    }
    if (s_config.pd_options[ESP_PD_DOMAIN_RTC_PERIPH] != ESP_PD_OPTION_ON) {
        pd_flags |= RTC_SLEEP_PD_RTC_PERIPH;
    }
    if (s_config.pd_options[ESP_PD_DOMAIN_XTAL] != ESP_PD_OPTION_ON) {
        pd_flags |= RTC_SLEEP_PD_XTAL;
    }

    if ((s_config.wakeup_triggers & (RTC_TOUCH_TRIG_EN | RTC_ULP_TRIG_EN)) == 0) {
    // If enabled EXT1 only and enable the additional current by touch, should be keep RTC_PERIPH power on.
#if ((defined CONFIG_ESP32_RTC_CLK_SRC_EXT_CRYS) && (defined CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_CURRENT))
    pd_flags &= ~RTC_SLEEP_PD_RTC_PERIPH;
#endif
    }
    return pd_flags;
}