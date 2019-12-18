#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {scalar_t__ id; int /*<<< orphan*/  param; int /*<<< orphan*/  (* fp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* ctrl; int /*<<< orphan*/  state; int /*<<< orphan*/  executedBy; } ;
typedef  TYPE_2__ tmr_obj_t ;
typedef  int /*<<< orphan*/  tmr_h ;
struct TYPE_4__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_STATE_EXPIRED ; 
 int /*<<< orphan*/  TIMER_STATE_STOPPED ; 
 scalar_t__ TIMER_STATE_WAITING ; 
 int /*<<< orphan*/  atomic_store_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_val_compare_exchange_8 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removeTimer (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetPthreadId () ; 
 int /*<<< orphan*/  timerDecRef (TYPE_2__*) ; 
 int /*<<< orphan*/  tmrTrace (char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 

__attribute__((used)) static void processExpiredTimer(void* handle, void* arg) {
  tmr_obj_t* timer = (tmr_obj_t*)handle;
  timer->executedBy = taosGetPthreadId();
  uint8_t state = atomic_val_compare_exchange_8(&timer->state, TIMER_STATE_WAITING, TIMER_STATE_EXPIRED);
  if (state == TIMER_STATE_WAITING) {
    const char* fmt = "%s timer[id=%lld, fp=%p, param=%p] execution start.";
    tmrTrace(fmt, timer->ctrl->label, timer->id, timer->fp, timer->param);

    (*timer->fp)(timer->param, (tmr_h)timer->id);
    atomic_store_8(&timer->state, TIMER_STATE_STOPPED);

    fmt = "%s timer[id=%lld, fp=%p, param=%p] execution end.";
    tmrTrace(fmt, timer->ctrl->label, timer->id, timer->fp, timer->param);
  }
  removeTimer(timer->id);
  timerDecRef(timer);
}