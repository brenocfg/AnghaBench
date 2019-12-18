#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ COND_EXEC ; 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
arm_no_early_alu_shift_value_dep (rtx producer, rtx consumer)
{
  rtx value = PATTERN (producer);
  rtx op = PATTERN (consumer);
  rtx early_op;

  if (GET_CODE (value) == COND_EXEC)
    value = COND_EXEC_CODE (value);
  if (GET_CODE (value) == PARALLEL)
    value = XVECEXP (value, 0, 0);
  value = XEXP (value, 0);
  if (GET_CODE (op) == COND_EXEC)
    op = COND_EXEC_CODE (op);
  if (GET_CODE (op) == PARALLEL)
    op = XVECEXP (op, 0, 0);
  op = XEXP (op, 1);

  early_op = XEXP (op, 0);

  /* This is either an actual independent shift, or a shift applied to
     the first operand of another operation.  We want the value being
     shifted, in either case.  */
  if (GET_CODE (early_op) != REG)
    early_op = XEXP (early_op, 0);

  return !reg_overlap_mentioned_p (value, early_op);
}