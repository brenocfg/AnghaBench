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
 int /*<<< orphan*/  TIMERG0 ; 
 int /*<<< orphan*/  TIMERG1 ; 
 int /*<<< orphan*/  timer_ll_wdt_set_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_protect (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void disableAllWdts(void)
{
    timer_ll_wdt_set_protect(&TIMERG0, false);
    timer_ll_wdt_set_enable(&TIMERG0, false);
    timer_ll_wdt_set_protect(&TIMERG0, true);

    timer_ll_wdt_set_protect(&TIMERG1, false);
    timer_ll_wdt_set_enable(&TIMERG1, false);
    timer_ll_wdt_set_protect(&TIMERG1, true);
}