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

/* Variables and functions */
 int /*<<< orphan*/  APPTRACE_ONPANIC_HOST_FLUSH_TMO ; 
 int /*<<< orphan*/  CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_THRESH ; 
 int /*<<< orphan*/  ESP_APPTRACE_DEST_TRAX ; 
 int /*<<< orphan*/  SEGGER_RTT_ESP32_FlushNoLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int abort_called ; 
 int /*<<< orphan*/  esp_apptrace_flush_nolock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_cpu_in_ocd_debug_mode () ; 

__attribute__((used)) static __attribute__((noreturn)) inline void invoke_abort(void)
{
    abort_called = true;
#if CONFIG_ESP32_APPTRACE_ENABLE
#if CONFIG_SYSVIEW_ENABLE
    SEGGER_RTT_ESP32_FlushNoLock(CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_THRESH, APPTRACE_ONPANIC_HOST_FLUSH_TMO);
#else
    esp_apptrace_flush_nolock(ESP_APPTRACE_DEST_TRAX, CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_THRESH,
                              APPTRACE_ONPANIC_HOST_FLUSH_TMO);
#endif
#endif
    while (1) {
        if (esp_cpu_in_ocd_debug_mode()) {
            __asm__ ("break 0,0");
        }
        *((int *) 0) = 0;
    }
}