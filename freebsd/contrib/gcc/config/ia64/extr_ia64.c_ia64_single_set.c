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
#define  CODE_FOR_epilogue_deallocate_stack 129 
#define  CODE_FOR_prologue_allocate_stack 128 
 scalar_t__ COND_EXEC ; 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int recog_memoized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_set_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
ia64_single_set (rtx insn)
{
  rtx x = PATTERN (insn), ret;
  if (GET_CODE (x) == COND_EXEC)
    x = COND_EXEC_CODE (x);
  if (GET_CODE (x) == SET)
    return x;

  /* Special case here prologue_allocate_stack and epilogue_deallocate_stack.
     Although they are not classical single set, the second set is there just
     to protect it from moving past FP-relative stack accesses.  */
  switch (recog_memoized (insn))
    {
    case CODE_FOR_prologue_allocate_stack:
    case CODE_FOR_epilogue_deallocate_stack:
      ret = XVECEXP (x, 0, 0);
      break;

    default:
      ret = single_set_2 (insn, x);
      break;
    }

  return ret;
}