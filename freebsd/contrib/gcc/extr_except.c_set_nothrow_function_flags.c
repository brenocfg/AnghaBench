#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_2__ {int all_throwers_are_sibcalls; } ;
typedef  int TREE_NOTHROW ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_P (scalar_t__) ; 
 scalar_t__ DECL_REPLACEABLE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  SIBLING_CALL_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ can_throw_external (scalar_t__) ; 
 TYPE_1__* cfun ; 
 int current_function_decl ; 
 scalar_t__ current_function_epilogue_delay_list ; 
 int /*<<< orphan*/  flag_exceptions ; 
 scalar_t__ get_insns () ; 

unsigned int
set_nothrow_function_flags (void)
{
  rtx insn;

  /* If we don't know that this implementation of the function will
     actually be used, then we must not set TREE_NOTHROW, since
     callers must not assume that this function does not throw.  */
  if (DECL_REPLACEABLE_P (current_function_decl))
    return 0;

  TREE_NOTHROW (current_function_decl) = 1;

  /* Assume cfun->all_throwers_are_sibcalls until we encounter
     something that can throw an exception.  We specifically exempt
     CALL_INSNs that are SIBLING_CALL_P, as these are really jumps,
     and can't throw.  Most CALL_INSNs are not SIBLING_CALL_P, so this
     is optimistic.  */

  cfun->all_throwers_are_sibcalls = 1;

  if (! flag_exceptions)
    return 0;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    if (can_throw_external (insn))
      {
        TREE_NOTHROW (current_function_decl) = 0;

	if (!CALL_P (insn) || !SIBLING_CALL_P (insn))
	  {
	    cfun->all_throwers_are_sibcalls = 0;
	    return 0;
	  }
      }

  for (insn = current_function_epilogue_delay_list; insn;
       insn = XEXP (insn, 1))
    if (can_throw_external (insn))
      {
        TREE_NOTHROW (current_function_decl) = 0;

	if (!CALL_P (insn) || !SIBLING_CALL_P (insn))
	  {
	    cfun->all_throwers_are_sibcalls = 0;
	    return 0;
	  }
      }
  return 0;
}