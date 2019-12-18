#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ operatorT ;
struct TYPE_4__ {scalar_t__ X_op; scalar_t__ X_add_number; int /*<<< orphan*/  X_add_symbol; int /*<<< orphan*/  X_op_symbol; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ O_subtract ; 
 scalar_t__ O_symbol ; 
 scalar_t__ THUMB_IS_FUNC (int /*<<< orphan*/ ) ; 

int
arm_optimize_expr (expressionS *l, operatorT op, expressionS *r)
{
  if (op == O_subtract
      && l->X_op == O_symbol
      && r->X_op == O_symbol
      && THUMB_IS_FUNC (l->X_add_symbol))
    {
      l->X_op = O_subtract;
      l->X_op_symbol = r->X_add_symbol;
      l->X_add_number -= r->X_add_number;
      return 1;
    }
  /* Process as normal.  */
  return 0;
}