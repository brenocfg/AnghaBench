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
typedef  enum attr_i387_cw { ____Placeholder_attr_i387_cw } attr_i387_cw ;

/* Variables and functions */
 scalar_t__ ASM_INPUT ; 
 scalar_t__ CALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
#define  I387_CEIL 131 
 int I387_CW_ANY ; 
 int I387_CW_CEIL ; 
 int I387_CW_FLOOR ; 
 int I387_CW_MASK_PM ; 
 int I387_CW_TRUNC ; 
 int I387_CW_UNINITIALIZED ; 
#define  I387_FLOOR 130 
#define  I387_MASK_PM 129 
#define  I387_TRUNC 128 
 scalar_t__ NONJUMP_INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ asm_noperands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int get_attr_i387_cw (int /*<<< orphan*/ ) ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 

int
ix86_mode_needed (int entity, rtx insn)
{
  enum attr_i387_cw mode;

  /* The mode UNINITIALIZED is used to store control word after a
     function call or ASM pattern.  The mode ANY specify that function
     has no requirements on the control word and make no changes in the
     bits we are interested in.  */

  if (CALL_P (insn)
      || (NONJUMP_INSN_P (insn)
	  && (asm_noperands (PATTERN (insn)) >= 0
	      || GET_CODE (PATTERN (insn)) == ASM_INPUT)))
    return I387_CW_UNINITIALIZED;

  if (recog_memoized (insn) < 0)
    return I387_CW_ANY;

  mode = get_attr_i387_cw (insn);

  switch (entity)
    {
    case I387_TRUNC:
      if (mode == I387_CW_TRUNC)
	return mode;
      break;

    case I387_FLOOR:
      if (mode == I387_CW_FLOOR)
	return mode;
      break;

    case I387_CEIL:
      if (mode == I387_CW_CEIL)
	return mode;
      break;

    case I387_MASK_PM:
      if (mode == I387_CW_MASK_PM)
	return mode;
      break;

    default:
      gcc_unreachable ();
    }

  return I387_CW_ANY;
}