#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_3__ {int oper; int /*<<< orphan*/  operand2; int /*<<< orphan*/  operand1; } ;
typedef  TYPE_1__ rc_condition_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  RC_CONDITION_EQ 133 
#define  RC_CONDITION_GE 132 
#define  RC_CONDITION_GT 131 
#define  RC_CONDITION_LE 130 
#define  RC_CONDITION_LT 129 
#define  RC_CONDITION_NE 128 
 unsigned int rc_evaluate_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int rc_test_condition(rc_condition_t* self, unsigned add_buffer, rc_peek_t peek, void* ud, lua_State* L) {
  unsigned value1 = rc_evaluate_operand(&self->operand1, peek, ud, L) + add_buffer;
  unsigned value2 = rc_evaluate_operand(&self->operand2, peek, ud, L);

  switch (self->oper) {
    case RC_CONDITION_EQ: return value1 == value2;
    case RC_CONDITION_NE: return value1 != value2;
    case RC_CONDITION_LT: return value1 < value2;
    case RC_CONDITION_LE: return value1 <= value2;
    case RC_CONDITION_GT: return value1 > value2;
    case RC_CONDITION_GE: return value1 >= value2;
    default: return 1;
  }
}