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
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_5__ {TYPE_2__* conditions; } ;
typedef  TYPE_1__ rc_condset_t ;
struct TYPE_6__ {int pause; int type; scalar_t__ required_hits; scalar_t__ current_hits; int /*<<< orphan*/  operand1; struct TYPE_6__* next; } ;
typedef  TYPE_2__ rc_condition_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  RC_CONDITION_ADD_HITS 133 
#define  RC_CONDITION_ADD_SOURCE 132 
#define  RC_CONDITION_AND_NEXT 131 
#define  RC_CONDITION_PAUSE_IF 130 
#define  RC_CONDITION_RESET_IF 129 
#define  RC_CONDITION_SUB_SOURCE 128 
 unsigned int rc_evaluate_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int rc_test_condition (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc_test_condset_internal(rc_condset_t* self, int processing_pause, int* reset, rc_peek_t peek, void* ud, lua_State* L) {
  rc_condition_t* condition;
  int set_valid, cond_valid, prev_cond;
  unsigned add_buffer, add_hits;

  set_valid = 1;
  prev_cond = 1;
  add_buffer = add_hits = 0;

  for (condition = self->conditions; condition != 0; condition = condition->next) {
    if (condition->pause != processing_pause) {
      continue;
    }

    switch (condition->type) {
      case RC_CONDITION_ADD_SOURCE:
        add_buffer += rc_evaluate_operand(&condition->operand1, peek, ud, L);
        continue;
      
      case RC_CONDITION_SUB_SOURCE:
        add_buffer -= rc_evaluate_operand(&condition->operand1, peek, ud, L);
        continue;
      
      case RC_CONDITION_ADD_HITS:
        if (rc_test_condition(condition, add_buffer, peek, ud, L)) {
          if (condition->required_hits == 0 || condition->current_hits < condition->required_hits) {
            condition->current_hits++;
          }
        }

        add_buffer = 0;
        add_hits += condition->current_hits;
        continue;

      case RC_CONDITION_AND_NEXT:
        prev_cond &= rc_test_condition(condition, add_buffer, peek, ud, L);
        add_buffer = 0;
        continue;
    }

    /* always evaluate the condition to ensure delta values get tracked correctly */
    cond_valid = rc_test_condition(condition, add_buffer, peek, ud, L);

    /* merge AndNext value and reset it for the next condition */
    cond_valid &= prev_cond;
    prev_cond = 1;

    /* if the condition has a target hit count that has already been met, it's automatically true, even if not currently true. */
    if (condition->required_hits != 0 && (condition->current_hits + add_hits) >= condition->required_hits) {
      cond_valid = 1;
    }
    else if (cond_valid) {
      condition->current_hits++;

      if (condition->required_hits == 0) {
        /* not a hit-based requirement: ignore any additional logic! */
      }
      else if ((condition->current_hits + add_hits) < condition->required_hits) {
        /* HitCount target has not yet been met, condition is not yet valid */
        cond_valid = 0;
      }
    }

    /* reset AddHits and AddSource/SubSource values */
    add_buffer = add_hits = 0;

    switch (condition->type) {
      case RC_CONDITION_PAUSE_IF:
        /* as soon as we find a PauseIf that evaluates to true, stop processing the rest of the group */
        if (cond_valid) {
          return 1;
        }

        /* if we make it to the end of the function, make sure we indicate that nothing matched. if we do find
           a later PauseIf match, it'll automatically return true via the previous condition. */
        set_valid = 0;

        if (condition->required_hits == 0) {
          /* PauseIf didn't evaluate true, and doesn't have a HitCount, reset the HitCount to indicate the condition didn't match */
          condition->current_hits = 0;
        }
        else {
          /* PauseIf has a HitCount that hasn't been met, ignore it for now. */
        }

        break;
      
      case RC_CONDITION_RESET_IF:
        if (cond_valid) {
          *reset = 1; /* let caller know to reset all hit counts */
          set_valid = 0; /* cannot be valid if we've hit a reset condition */
        }

        break;

      default:
        set_valid &= cond_valid;
        break;
    }
  }

  return set_valid;
}