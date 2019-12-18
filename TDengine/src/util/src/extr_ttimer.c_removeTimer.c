#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {uintptr_t id; struct TYPE_7__* mnext; } ;
typedef  TYPE_1__ tmr_obj_t ;
struct TYPE_8__ {TYPE_1__* timers; } ;
typedef  TYPE_2__ timer_list_t ;
struct TYPE_9__ {uintptr_t size; TYPE_2__* slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockTimerList (TYPE_2__*) ; 
 int /*<<< orphan*/  timerDecRef (TYPE_1__*) ; 
 TYPE_4__ timerMap ; 
 int /*<<< orphan*/  unlockTimerList (TYPE_2__*) ; 

__attribute__((used)) static void removeTimer(uintptr_t id) {
  tmr_obj_t*    prev = NULL;
  uint32_t      idx = (uint32_t)(id % timerMap.size);
  timer_list_t* list = timerMap.slots + idx;
  lockTimerList(list);
  for (tmr_obj_t* p = list->timers; p != NULL; p = p->mnext) {
    if (p->id == id) {
      if (prev == NULL) {
        list->timers = p->mnext;
      } else {
        prev->mnext = p->mnext;
      }
      timerDecRef(p);
      break;
    }
    prev = p;
  }
  unlockTimerList(list);
}