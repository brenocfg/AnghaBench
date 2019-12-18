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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ DEEPSLEEP_RESET ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int SOC_RTC_DATA_HIGH ; 
 int SOC_RTC_DATA_LOW ; 
 int SOC_RTC_DRAM_HIGH ; 
 int SOC_RTC_DRAM_LOW ; 
 int SOC_RTC_IRAM_HIGH ; 
 int SOC_RTC_IRAM_LOW ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ rtc_get_reset_reason (int /*<<< orphan*/ ) ; 
 scalar_t__ should_map (int) ; 

__attribute__((used)) static bool should_load(uint32_t load_addr)
{
    /* Reload the RTC memory segments whenever a non-deepsleep reset
       is occurring */
    bool load_rtc_memory = rtc_get_reset_reason(0) != DEEPSLEEP_RESET;

    if (should_map(load_addr)) {
        return false;
    }

    if (load_addr < 0x10000000) {
        // Reserved for non-loaded addresses.
        // Current reserved values are
        // 0x0 (padding block)
        // 0x4 (unused, but reserved for an MD5 block)
        return false;
    }

    if (!load_rtc_memory) {
        if (load_addr >= SOC_RTC_IRAM_LOW && load_addr < SOC_RTC_IRAM_HIGH) {
            ESP_LOGD(TAG, "Skipping RTC fast memory segment at 0x%08x", load_addr);
            return false;
        }
        if (load_addr >= SOC_RTC_DRAM_LOW && load_addr < SOC_RTC_DRAM_HIGH) {
            ESP_LOGD(TAG, "Skipping RTC fast memory segment at 0x%08x", load_addr);
            return false;
        }
        if (load_addr >= SOC_RTC_DATA_LOW && load_addr < SOC_RTC_DATA_HIGH) {
            ESP_LOGD(TAG, "Skipping RTC slow memory segment at 0x%08x", load_addr);
            return false;
        }
    }

    return true;
}