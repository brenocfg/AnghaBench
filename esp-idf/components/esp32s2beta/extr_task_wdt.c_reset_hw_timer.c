#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int has_reset; struct TYPE_4__* next; } ;
typedef  TYPE_1__ twdt_task_t ;
struct TYPE_6__ {int wdt_feed; scalar_t__ wdt_wprotect; } ;
struct TYPE_5__ {TYPE_1__* list; } ;

/* Variables and functions */
 TYPE_3__ TIMERG0 ; 
 scalar_t__ TIMG_WDT_WKEY_VALUE ; 
 TYPE_2__* twdt_config ; 

__attribute__((used)) static void reset_hw_timer(void)
{
    //All tasks have reset; time to reset the hardware timer.
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;
    //Clear all has_reset flags in list
    for (twdt_task_t *task = twdt_config->list; task != NULL; task = task->next){
        task->has_reset=false;
    }
}