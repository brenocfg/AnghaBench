#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {uintptr_t id; int /*<<< orphan*/  wheel; void* param; int /*<<< orphan*/  fp; TYPE_2__* ctrl; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tmr_obj_t ;
struct TYPE_10__ {int /*<<< orphan*/  label; } ;
typedef  TYPE_2__ tmr_ctrl_t ;
typedef  int /*<<< orphan*/  TAOS_TMR_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_STATE_WAITING ; 
 int /*<<< orphan*/  addTimer (TYPE_1__*) ; 
 int /*<<< orphan*/  addToExpired (TYPE_1__*) ; 
 int /*<<< orphan*/  addToWheel (TYPE_1__*,int) ; 
 uintptr_t getNextTimerId () ; 
 int /*<<< orphan*/  tListLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timerAddRef (TYPE_1__*) ; 
 int /*<<< orphan*/  tmrTrace (char const*,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wheels ; 

__attribute__((used)) static uintptr_t doStartTimer(tmr_obj_t* timer, TAOS_TMR_CALLBACK fp, int mseconds, void* param, tmr_ctrl_t* ctrl) {
  uintptr_t id = getNextTimerId();
  timer->id = id;
  timer->state = TIMER_STATE_WAITING;
  timer->fp = fp;
  timer->param = param;
  timer->ctrl = ctrl;
  addTimer(timer);

  const char* fmt = "%s timer[id=%lld, fp=%p, param=%p] started";
  tmrTrace(fmt, ctrl->label, timer->id, timer->fp, timer->param);

  if (mseconds == 0) {
    timer->wheel = tListLen(wheels);
    timerAddRef(timer);
    addToExpired(timer);
  } else {
    addToWheel(timer, mseconds);
  }

  // note: use `timer->id` here is unsafe as `timer` may already be freed
  return id;
}