#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ force; } ;
typedef  TYPE_1__ rtc_vddsdio_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int RTC_SLEEP_PD_VDDSDIO ; 
 int /*<<< orphan*/  esp_sleep_start (int) ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  rtc_vddsdio_set_config (TYPE_1__) ; 

__attribute__((used)) static esp_err_t esp_light_sleep_inner(uint32_t pd_flags,
        uint32_t flash_enable_time_us,
        rtc_vddsdio_config_t vddsdio_config)
{
    // Enter sleep
    esp_err_t err = esp_sleep_start(pd_flags);

    // If VDDSDIO regulator was controlled by RTC registers before sleep,
    // restore the configuration.
    if (vddsdio_config.force) {
        rtc_vddsdio_set_config(vddsdio_config);
    }

    // If SPI flash was powered down, wait for it to become ready
    if (pd_flags & RTC_SLEEP_PD_VDDSDIO) {
        // Wait for the flash chip to start up
        ets_delay_us(flash_enable_time_us);
    }
    return err;
}