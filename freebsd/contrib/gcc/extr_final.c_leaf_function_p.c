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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ SEQUENCE ; 
 int /*<<< orphan*/  SIBLING_CALL_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ current_function_epilogue_delay_list ; 
 scalar_t__ current_function_profile ; 
 scalar_t__ get_insns () ; 
 scalar_t__ profile_arc_flag ; 

int
leaf_function_p (void)
{
  rtx insn;
  rtx link;

  if (current_function_profile || profile_arc_flag)
    return 0;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      if (CALL_P (insn)
	  && ! SIBLING_CALL_P (insn))
	return 0;
      if (NONJUMP_INSN_P (insn)
	  && GET_CODE (PATTERN (insn)) == SEQUENCE
	  && CALL_P (XVECEXP (PATTERN (insn), 0, 0))
	  && ! SIBLING_CALL_P (XVECEXP (PATTERN (insn), 0, 0)))
	return 0;
    }
  for (link = current_function_epilogue_delay_list;
       link;
       link = XEXP (link, 1))
    {
      insn = XEXP (link, 0);

      if (CALL_P (insn)
	  && ! SIBLING_CALL_P (insn))
	return 0;
      if (NONJUMP_INSN_P (insn)
	  && GET_CODE (PATTERN (insn)) == SEQUENCE
	  && CALL_P (XVECEXP (PATTERN (insn), 0, 0))
	  && ! SIBLING_CALL_P (XVECEXP (PATTERN (insn), 0, 0)))
	return 0;
    }

  return 1;
}