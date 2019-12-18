#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {uintptr_t id; struct TYPE_8__* mnext; } ;
typedef  TYPE_1__ tmr_obj_t ;
struct TYPE_9__ {TYPE_1__* timers; } ;
typedef  TYPE_2__ timer_list_t ;
struct TYPE_10__ {uintptr_t size; TYPE_2__* slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockTimerList (TYPE_2__*) ; 
 int /*<<< orphan*/  timerAddRef (TYPE_1__*) ; 
 TYPE_4__ timerMap ; 
 int /*<<< orphan*/  unlockTimerList (TYPE_2__*) ; 

__attribute__((used)) static tmr_obj_t* findTimer(uintptr_t id) {
  tmr_obj_t* timer = NULL;
  if (id > 0) {
    uint32_t      idx = (uint32_t)(id % timerMap.size);
    timer_list_t* list = timerMap.slots + idx;
    lockTimerList(list);
    for (timer = list->timers; timer != NULL; timer = timer->mnext) {
      if (timer->id == id) {
        timerAddRef(timer);
        break;
      }
    }
    unlockTimerList(list);
  }
  return timer;
}