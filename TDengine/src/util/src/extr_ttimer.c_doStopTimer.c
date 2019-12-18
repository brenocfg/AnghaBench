#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {scalar_t__ executedBy; int /*<<< orphan*/  param; int /*<<< orphan*/  fp; int /*<<< orphan*/  id; TYPE_1__* ctrl; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ tmr_obj_t ;
struct TYPE_5__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 scalar_t__ TIMER_STATE_EXPIRED ; 
 scalar_t__ TIMER_STATE_STOPPED ; 
 scalar_t__ TIMER_STATE_WAITING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_load_8 (int /*<<< orphan*/ *) ; 
 scalar_t__ removeFromWheel (TYPE_2__*) ; 
 int /*<<< orphan*/  removeTimer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_yield () ; 
 scalar_t__ taosGetPthreadId () ; 
 int /*<<< orphan*/  tmrTrace (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool doStopTimer(tmr_obj_t* timer, uint8_t state) {
  bool reusable = false;

  if (state == TIMER_STATE_WAITING) {
    if (removeFromWheel(timer)) {
      removeTimer(timer->id);
      // only safe to reuse the timer when timer is removed from the wheel.
      // we cannot guarantee the thread safety of the timr in all other cases.
      reusable = true;
    }
    const char* fmt = "%s timer[id=%lld, fp=%p, param=%p] is cancelled.";
    tmrTrace(fmt, timer->ctrl->label, timer->id, timer->fp, timer->param);
  } else if (state != TIMER_STATE_EXPIRED) {
    // timer already stopped or cancelled, has nothing to do in this case
  } else if (timer->executedBy == taosGetPthreadId()) {
    // taosTmrReset is called in the timer callback, should do nothing in this
    // case to avoid dead lock. note taosTmrReset must be the last statement
    // of the callback funtion, will be a bug otherwise.
  } else {
    assert(timer->executedBy != taosGetPthreadId());

    const char* fmt = "%s timer[id=%lld, fp=%p, param=%p] fired, waiting...";
    tmrTrace(fmt, timer->ctrl->label, timer->id, timer->fp, timer->param);

    for (int i = 1; atomic_load_8(&timer->state) != TIMER_STATE_STOPPED; i++) {
      if (i % 1000 == 0) {
        sched_yield();
      }
    }

    fmt = "%s timer[id=%lld, fp=%p, param=%p] stopped.";
    tmrTrace(fmt, timer->ctrl->label, timer->id, timer->fp, timer->param);
  }

  return reusable;
}