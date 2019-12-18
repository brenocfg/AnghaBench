#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  counter_en; int /*<<< orphan*/  intr_type; int /*<<< orphan*/  divider; int /*<<< orphan*/  counter_dir; int /*<<< orphan*/  auto_reload; int /*<<< orphan*/  alarm_en; } ;
typedef  TYPE_1__ timer_config_t ;
typedef  scalar_t__ esp_err_t ;
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MB_PORT_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MB_PORT_TIMER_ISR_FLAG ; 
 int /*<<< orphan*/  MB_TIMER_PRESCALLER ; 
 int /*<<< orphan*/  MB_TIMER_WITH_RELOAD ; 
 int /*<<< orphan*/  TIMER_ALARM_EN ; 
 int /*<<< orphan*/  TIMER_COUNT_UP ; 
 int /*<<< orphan*/  TIMER_INTR_LEVEL ; 
 int /*<<< orphan*/  TIMER_PAUSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ timer_init (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 scalar_t__ timer_isr_register (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pause (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ timer_set_alarm_value (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ timer_set_counter_value (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  usTimerGroupIndex ; 
 scalar_t__ usTimerIndex ; 
 int /*<<< orphan*/  vTimerGroupIsr ; 
 int /*<<< orphan*/  xTimerIntHandle ; 

BOOL xMBPortTimersInit(USHORT usTim1Timerout50us)
{
#ifdef CONFIG_FMB_TIMER_PORT_ENABLED
    MB_PORT_CHECK((usTim1Timerout50us > 0), FALSE,
            "Modbus timeout discreet is incorrect.");
    esp_err_t xErr;
    timer_config_t config;
    config.alarm_en = TIMER_ALARM_EN;
    config.auto_reload = MB_TIMER_WITH_RELOAD;
    config.counter_dir = TIMER_COUNT_UP;
    config.divider = MB_TIMER_PRESCALLER;
    config.intr_type = TIMER_INTR_LEVEL;
    config.counter_en = TIMER_PAUSE;
    // Configure timer
    xErr = timer_init(usTimerGroupIndex, usTimerIndex, &config);
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
            "timer init failure, timer_init() returned (0x%x).", (uint32_t)xErr);
    // Stop timer counter
    xErr = timer_pause(usTimerGroupIndex, usTimerIndex);
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
                    "stop timer failure, timer_pause() returned (0x%x).", (uint32_t)xErr);
    // Reset counter value
    xErr = timer_set_counter_value(usTimerGroupIndex, usTimerIndex, 0x00000000ULL);
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
                    "timer set value failure, timer_set_counter_value() returned (0x%x).",
                    (uint32_t)xErr);
    // wait3T5_us = 35 * 11 * 100000 / baud; // the 3.5T symbol time for baudrate
    // Set alarm value for usTim1Timerout50us * 50uS
    xErr = timer_set_alarm_value(usTimerGroupIndex, usTimerIndex, (uint32_t)(usTim1Timerout50us));
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
                    "failure to set alarm failure, timer_set_alarm_value() returned (0x%x).",
                    (uint32_t)xErr);
    // Register ISR for timer
    xErr = timer_isr_register(usTimerGroupIndex, usTimerIndex, vTimerGroupIsr,
                                (void*)(uint32_t)usTimerIndex, MB_PORT_TIMER_ISR_FLAG, &xTimerIntHandle);
    MB_PORT_CHECK((xErr == ESP_OK), FALSE,
                    "timer set value failure, timer_isr_register() returned (0x%x).",
                    (uint32_t)xErr);
#endif
    return TRUE;
}