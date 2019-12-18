#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tmr_obj_t ;
typedef  int /*<<< orphan*/  tmr_h ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_STATE_CANCELED ; 
 scalar_t__ TIMER_STATE_WAITING ; 
 scalar_t__ atomic_val_compare_exchange_8 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doStopTimer (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* findTimer (uintptr_t) ; 
 int /*<<< orphan*/  timerDecRef (TYPE_1__*) ; 
 int /*<<< orphan*/  tmrTrace (char*,uintptr_t) ; 

bool taosTmrStop(tmr_h timerId) {
  uintptr_t id = (uintptr_t)timerId;

  tmr_obj_t* timer = findTimer(id);
  if (timer == NULL) {
    tmrTrace("timer[id=%lld] does not exist", id);
    return false;
  }

  uint8_t state = atomic_val_compare_exchange_8(&timer->state, TIMER_STATE_WAITING, TIMER_STATE_CANCELED);
  doStopTimer(timer, state);
  timerDecRef(timer);

  return state == TIMER_STATE_WAITING;
}