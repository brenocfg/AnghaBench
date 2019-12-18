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
 int TG0_WDT_TICK_US ; 
 int /*<<< orphan*/  TIMERG0 ; 
 int /*<<< orphan*/  TIMERG1 ; 
 int /*<<< orphan*/  TIMER_WDT_RESET_SYSTEM ; 
 int /*<<< orphan*/  timer_ll_wdt_feed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_ll_wdt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_protect (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_tick (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_timeout_behavior (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reconfigureAllWdts(void)
{
    timer_ll_wdt_set_protect(&TIMERG0, false);
    timer_ll_wdt_feed(&TIMERG0);
    timer_ll_wdt_init(&TIMERG0);
    timer_ll_wdt_set_tick(&TIMERG0, TG0_WDT_TICK_US); //Prescaler: wdt counts in ticks of TG0_WDT_TICK_US
    //1st stage timeout: reset system
    timer_ll_wdt_set_timeout_behavior(&TIMERG0, 0, TIMER_WDT_RESET_SYSTEM);
    //1 second before reset
    timer_ll_wdt_set_timeout(&TIMERG0, 0, 1000*1000/TG0_WDT_TICK_US);
    timer_ll_wdt_set_enable(&TIMERG0, true);
    timer_ll_wdt_set_protect(&TIMERG0, true);

    //Disable wdt 1
    timer_ll_wdt_set_protect(&TIMERG1, false);
    timer_ll_wdt_set_enable(&TIMERG1, false);
    timer_ll_wdt_set_protect(&TIMERG1, true);
}