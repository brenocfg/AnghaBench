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
typedef  int /*<<< orphan*/  esp_reset_reason_t ;
typedef  int RESET_REASON ;

/* Variables and functions */
#define  DEEPSLEEP_RESET 142 
 int /*<<< orphan*/  ESP_RST_BROWNOUT ; 
 int /*<<< orphan*/  ESP_RST_DEEPSLEEP ; 
 int /*<<< orphan*/  ESP_RST_INT_WDT ; 
 int /*<<< orphan*/  ESP_RST_PANIC ; 
 int /*<<< orphan*/  ESP_RST_POWERON ; 
 int /*<<< orphan*/  ESP_RST_SDIO ; 
 int /*<<< orphan*/  ESP_RST_SW ; 
 int /*<<< orphan*/  ESP_RST_TASK_WDT ; 
 int /*<<< orphan*/  ESP_RST_UNKNOWN ; 
 int /*<<< orphan*/  ESP_RST_WDT ; 
#define  EXT_CPU_RESET 141 
#define  INTRUSION_RESET 140 
#define  OWDT_RESET 139 
#define  POWERON_RESET 138 
#define  RTCWDT_BROWN_OUT_RESET 137 
#define  RTCWDT_CPU_RESET 136 
#define  RTCWDT_RTC_RESET 135 
#define  RTCWDT_SYS_RESET 134 
#define  SDIO_RESET 133 
#define  SW_CPU_RESET 132 
#define  SW_RESET 131 
#define  TG0WDT_SYS_RESET 130 
#define  TG1WDT_SYS_RESET 129 
#define  TGWDT_CPU_RESET 128 

__attribute__((used)) static esp_reset_reason_t get_reset_reason(RESET_REASON rtc_reset_reason, esp_reset_reason_t reset_reason_hint)
{
    switch (rtc_reset_reason) {
        case POWERON_RESET:
            return ESP_RST_POWERON;

        /* For ESP32, ESP_RST_EXT is never returned */


        case SW_CPU_RESET:
        case SW_RESET:
        case EXT_CPU_RESET: /* unused */
            if (reset_reason_hint == ESP_RST_PANIC ||
                reset_reason_hint == ESP_RST_BROWNOUT ||
                reset_reason_hint == ESP_RST_TASK_WDT ||
                reset_reason_hint == ESP_RST_INT_WDT) {
                return reset_reason_hint;
            }
            return ESP_RST_SW;

        case DEEPSLEEP_RESET:
            return ESP_RST_DEEPSLEEP;

        case TG0WDT_SYS_RESET:
            return ESP_RST_TASK_WDT;

        case TG1WDT_SYS_RESET:
            return ESP_RST_INT_WDT;

        case OWDT_RESET:
        case RTCWDT_SYS_RESET:
        case RTCWDT_RTC_RESET:
        case RTCWDT_CPU_RESET:  /* unused */
        case TGWDT_CPU_RESET:   /* unused */
            return ESP_RST_WDT;

        case RTCWDT_BROWN_OUT_RESET:    /* unused */
            return ESP_RST_BROWNOUT;

        case SDIO_RESET:
            return ESP_RST_SDIO;

        case INTRUSION_RESET: /* unused */
        default:
            return ESP_RST_UNKNOWN;
    }
}