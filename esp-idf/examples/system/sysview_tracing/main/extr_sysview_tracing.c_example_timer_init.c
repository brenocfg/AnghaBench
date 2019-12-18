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
typedef  unsigned long uint64_t ;
typedef  unsigned long uint32_t ;
struct TYPE_3__ {int alarm_en; int auto_reload; int divider; int /*<<< orphan*/  counter_en; int /*<<< orphan*/  intr_type; int /*<<< orphan*/  counter_dir; } ;
typedef  TYPE_1__ timer_config_t ;

/* Variables and functions */
 unsigned long TIMER_BASE_CLK ; 
 int /*<<< orphan*/  TIMER_COUNT_UP ; 
 int /*<<< orphan*/  TIMER_INTR_LEVEL ; 
 int /*<<< orphan*/  TIMER_PAUSE ; 
 int /*<<< orphan*/  timer_enable_intr (int,int) ; 
 int /*<<< orphan*/  timer_init (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  timer_pause (int,int) ; 
 int /*<<< orphan*/  timer_set_alarm_value (int,int,unsigned long) ; 
 int /*<<< orphan*/  timer_set_counter_value (int,int,int) ; 

__attribute__((used)) static void example_timer_init(int timer_group, int timer_idx, uint32_t period)
{
    timer_config_t config;
    uint64_t alarm_val = (period * (TIMER_BASE_CLK / 1000000UL)) / 2;

    config.alarm_en = 1;
    config.auto_reload = 1;
    config.counter_dir = TIMER_COUNT_UP;
    config.divider = 2;     //Range is 2 to 65536
    config.intr_type = TIMER_INTR_LEVEL;
    config.counter_en = TIMER_PAUSE;
    /*Configure timer*/
    timer_init(timer_group, timer_idx, &config);
    /*Stop timer counter*/
    timer_pause(timer_group, timer_idx);
    /*Load counter value */
    timer_set_counter_value(timer_group, timer_idx, 0x00000000ULL);
    /*Set alarm value*/
    timer_set_alarm_value(timer_group, timer_idx, alarm_val);
    /*Enable timer interrupt*/
    timer_enable_intr(timer_group, timer_idx);
}