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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  TS_TIMER_GROUP ; 
 int /*<<< orphan*/  TS_TIMER_ID ; 
 int /*<<< orphan*/  esp_timer_get_time () ; 
 int /*<<< orphan*/  portGET_RUN_TIME_COUNTER_VALUE () ; 
 int /*<<< orphan*/  timer_get_counter_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

U32 SEGGER_SYSVIEW_X_GetTimestamp(void)
{
#if TS_USE_TIMERGROUP
    uint64_t ts = 0;
    timer_get_counter_value(TS_TIMER_GROUP, TS_TIMER_ID, &ts);
    return (U32) ts; // return lower part of counter value
#elif TS_USE_CCOUNT
    return portGET_RUN_TIME_COUNTER_VALUE();
#elif TS_USE_ESP_TIMER
    return (U32) esp_timer_get_time(); // return lower part of counter value
#endif
}