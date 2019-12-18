#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int has_reset; struct TYPE_3__* next; } ;
typedef  TYPE_1__ twdt_task_t ;
struct TYPE_4__ {TYPE_1__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMERG0 ; 
 int /*<<< orphan*/  timer_ll_wdt_feed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_ll_wdt_set_protect (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* twdt_config ; 

__attribute__((used)) static void reset_hw_timer(void)
{
    //All tasks have reset; time to reset the hardware timer.
    timer_ll_wdt_set_protect(&TIMERG0, false);
    timer_ll_wdt_feed(&TIMERG0);
    timer_ll_wdt_set_protect(&TIMERG0, true);
    //Clear all has_reset flags in list
    for (twdt_task_t *task = twdt_config->list; task != NULL; task = task->next){
        task->has_reset=false;
    }
}