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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  timer_idx; int /*<<< orphan*/  timer_group; } ;
typedef  TYPE_1__ timer_info_t ;
typedef  int /*<<< orphan*/  timer_idx_t ;
typedef  int /*<<< orphan*/  timer_group_t ;

/* Variables and functions */
 double TIMER_SCALE ; 
 int alarm_flag ; 
 int /*<<< orphan*/  ets_printf (char*,double,...) ; 
 int /*<<< orphan*/  timer_get_alarm_value (int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__*) ; 
 int /*<<< orphan*/  timer_get_counter_time_sec (int /*<<< orphan*/  const,int /*<<< orphan*/  const,double*) ; 
 int /*<<< orphan*/  timer_get_counter_value (int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__*) ; 
 scalar_t__ timer_group_get_auto_reload_in_isr (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  timer_group_intr_clr_in_isr (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void test_timer_group_isr(void *para)
{
    timer_info_t* info = (timer_info_t*) para;
    const timer_group_t timer_group = info->timer_group;
    const timer_idx_t timer_idx = info->timer_idx;
    uint64_t timer_val;
    double time;
    uint64_t alarm_value;
    alarm_flag = true;
    if (timer_group_get_auto_reload_in_isr(timer_group, timer_idx)) {
        timer_group_intr_clr_in_isr(timer_group, timer_idx);
        ets_printf("This is TG%d timer[%d] reload-timer alarm!\n", timer_group, timer_idx);
        timer_get_counter_value(timer_group, timer_idx, &timer_val);
        timer_get_counter_time_sec(timer_group, timer_idx, &time);
        ets_printf("time: %.8f S\n", time);
    } else {
        timer_group_intr_clr_in_isr(timer_group, timer_idx);
        ets_printf("This is TG%d timer[%d] count-up-timer alarm!\n", timer_group, timer_idx);
        timer_get_counter_value(timer_group, timer_idx, &timer_val);
        timer_get_counter_time_sec(timer_group, timer_idx, &time);
        timer_get_alarm_value(timer_group, timer_idx, &alarm_value);
        ets_printf("time: %.8f S\n", time);
        double alarm_time = (double) alarm_value / TIMER_SCALE;
        ets_printf("alarm_time: %.8f S\n", alarm_time);
    }
}