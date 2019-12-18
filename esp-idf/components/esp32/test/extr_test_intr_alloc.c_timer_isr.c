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
 int /*<<< orphan*/  TIMER_0 ; 
 int /*<<< orphan*/  TIMER_1 ; 
 int /*<<< orphan*/  TIMER_GROUP_0 ; 
 int /*<<< orphan*/  TIMER_GROUP_1 ; 
 int /*<<< orphan*/ * count ; 
 int /*<<< orphan*/  timer_group_enable_alarm_in_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_group_intr_clr_in_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_isr(void *arg)
{
    int timer_idx = (int)arg;
    count[timer_idx]++;
    if (timer_idx==0) {
        timer_group_intr_clr_in_isr(TIMER_GROUP_0, TIMER_0);
        timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_0);
    }
    if (timer_idx==1) {
        timer_group_intr_clr_in_isr(TIMER_GROUP_0, TIMER_1);
        timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_1);
    }
    if (timer_idx==2) {
        timer_group_intr_clr_in_isr(TIMER_GROUP_1, TIMER_0);
        timer_group_enable_alarm_in_isr(TIMER_GROUP_1, TIMER_0);
    }
    if (timer_idx==3) {
        timer_group_intr_clr_in_isr(TIMER_GROUP_1, TIMER_1);
        timer_group_enable_alarm_in_isr(TIMER_GROUP_1, TIMER_1);
    }
//  ets_printf("int %d\n", timer_idx);
}