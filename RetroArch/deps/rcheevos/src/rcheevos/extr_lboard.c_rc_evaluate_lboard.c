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
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_5__ {scalar_t__ requirement; scalar_t__ alternative; } ;
struct TYPE_4__ {int submitted; int started; int /*<<< orphan*/  value; int /*<<< orphan*/ * progress; TYPE_2__ start; TYPE_2__ submit; TYPE_2__ cancel; int /*<<< orphan*/  memrefs; } ;
typedef  TYPE_1__ rc_lboard_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  RC_LBOARD_ACTIVE 132 
#define  RC_LBOARD_CANCELED 131 
#define  RC_LBOARD_INACTIVE 130 
#define  RC_LBOARD_STARTED 129 
#define  RC_LBOARD_TRIGGERED 128 
 unsigned int rc_evaluate_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int rc_test_trigger (TYPE_2__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_update_memref_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int rc_evaluate_lboard(rc_lboard_t* self, unsigned* value, rc_peek_t peek, void* peek_ud, lua_State* L) {
  int start_ok, cancel_ok, submit_ok;
  int action = -1;

  rc_update_memref_values(self->memrefs, peek, peek_ud);

  /* ASSERT: these are always tested once every frame, to ensure delta variables work properly */
  start_ok = rc_test_trigger(&self->start, peek, peek_ud, L);
  cancel_ok = rc_test_trigger(&self->cancel, peek, peek_ud, L);
  submit_ok = rc_test_trigger(&self->submit, peek, peek_ud, L);

  if (self->submitted) {
    /* if we've already submitted or canceled the leaderboard, don't reactivate it until it becomes inactive. */
    if (!start_ok) {
      self->submitted = 0;
    }
  }
  else if (!self->started) {
    /* leaderboard is not active, if the start condition is true, activate it */
    if (start_ok && !cancel_ok) {
      if (submit_ok) {
        /* start and submit both true in the same frame, just submit without announcing the leaderboard is available */
        action = RC_LBOARD_TRIGGERED;
        /* prevent multiple submissions/notifications */
        self->submitted = 1;
      }
      else if (self->start.requirement != 0 || self->start.alternative != 0) {
        self->started = 1;
        action = RC_LBOARD_STARTED;
      }
    }
  }
  else {
    /* leaderboard is active */
    if (cancel_ok) {
      /* cancel condition is true, deactivate the leaderboard */
      self->started = 0;
      action = RC_LBOARD_CANCELED;
      /* prevent multiple cancel notifications */
      self->submitted = 1;
    }
    else if (submit_ok) {
      /* submit condition is true, submit the current value */
      self->started = 0;
      action = RC_LBOARD_TRIGGERED;
      self->submitted = 1;
    }
  }

  if (action == -1) {
    action = self->started ? RC_LBOARD_ACTIVE : RC_LBOARD_INACTIVE;
  }

  /* Calculate the value */
  switch (action) {
    case RC_LBOARD_ACTIVE: /* fall through */
    case RC_LBOARD_STARTED:
      *value = rc_evaluate_value(self->progress != 0 ? self->progress : &self->value, peek, peek_ud, L);
      break;

    case RC_LBOARD_TRIGGERED:
      *value = rc_evaluate_value(&self->value, peek, peek_ud, L);
      break;

    case RC_LBOARD_INACTIVE:
    case RC_LBOARD_CANCELED:
      *value = 0;
      break;
  }

  return action;
}