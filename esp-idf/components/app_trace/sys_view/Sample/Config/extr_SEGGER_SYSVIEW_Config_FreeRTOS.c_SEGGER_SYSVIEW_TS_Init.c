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
struct TYPE_3__ {int /*<<< orphan*/  counter_en; int /*<<< orphan*/  divider; int /*<<< orphan*/  counter_dir; int /*<<< orphan*/  auto_reload; int /*<<< orphan*/  alarm_en; } ;
typedef  TYPE_1__ timer_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSVIEW_TIMER_DIV ; 
 int /*<<< orphan*/  TIMER_COUNT_UP ; 
 int /*<<< orphan*/  TS_TIMER_GROUP ; 
 int /*<<< orphan*/  TS_TIMER_ID ; 
 int /*<<< orphan*/  timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  timer_set_counter_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SEGGER_SYSVIEW_TS_Init(void)
{
    /* We only need to initialize something if we use Timer Group.
     * esp_timer and ccount can be used as is.
     */
#if TS_USE_TIMERGROUP
    timer_config_t config = {
        .alarm_en = 0,
        .auto_reload = 0,
        .counter_dir = TIMER_COUNT_UP,
        .divider = SYSVIEW_TIMER_DIV,
        .counter_en = 0
    };
    /* Configure timer */
    timer_init(TS_TIMER_GROUP, TS_TIMER_ID, &config);
    /* Load counter value */
    timer_set_counter_value(TS_TIMER_GROUP, TS_TIMER_ID, 0x00000000ULL);
    /* Start counting */
    timer_start(TS_TIMER_GROUP, TS_TIMER_ID);
#endif // TS_USE_TIMERGROUP
}