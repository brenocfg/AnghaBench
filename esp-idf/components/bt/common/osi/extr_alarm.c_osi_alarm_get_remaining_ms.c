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
typedef  int /*<<< orphan*/  period_ms_t ;
struct TYPE_3__ {int deadline_us; } ;
typedef  TYPE_1__ osi_alarm_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/ * alarm_mutex ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int esp_timer_get_time () ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ **) ; 

period_ms_t osi_alarm_get_remaining_ms(const osi_alarm_t *alarm)
{
    assert(alarm_mutex != NULL);
    int64_t dt_us = 0;

    osi_mutex_lock(&alarm_mutex, OSI_MUTEX_MAX_TIMEOUT);
    dt_us = alarm->deadline_us - esp_timer_get_time();
    osi_mutex_unlock(&alarm_mutex);

    return (dt_us > 0) ? (period_ms_t)(dt_us / 1000) : 0;
}