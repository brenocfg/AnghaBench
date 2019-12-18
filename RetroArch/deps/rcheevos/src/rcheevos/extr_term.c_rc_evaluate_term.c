#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double dbl; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ value; } ;
struct TYPE_6__ {unsigned int invert; TYPE_4__ operand2; TYPE_4__ operand1; } ;
typedef  TYPE_2__ rc_term_t ;
typedef  int /*<<< orphan*/  rc_peek_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ RC_OPERAND_FP ; 
 unsigned int rc_evaluate_operand (TYPE_4__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

unsigned rc_evaluate_term(rc_term_t* self, rc_peek_t peek, void* ud, lua_State* L) {
  unsigned value = rc_evaluate_operand(&self->operand1, peek, ud, L);

  if (self->operand2.type != RC_OPERAND_FP) {
    return value * (rc_evaluate_operand(&self->operand2, peek, ud, L) ^ self->invert);
  }

  return (unsigned)((double)value * self->operand2.value.dbl);
}