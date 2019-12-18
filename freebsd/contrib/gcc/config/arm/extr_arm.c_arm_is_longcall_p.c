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
 int CALL_LONG ; 
 int CALL_SHORT ; 
 scalar_t__ DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ENCODED_LONG_CALL_ATTR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ TARGET_LONG_CALLS ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ current_file_function_operand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ flag_function_sections ; 

int
arm_is_longcall_p (rtx sym_ref, int call_cookie, int call_symbol)
{
  if (!call_symbol)
    {
      if (GET_CODE (sym_ref) != MEM)
	return 0;

      sym_ref = XEXP (sym_ref, 0);
    }

  if (GET_CODE (sym_ref) != SYMBOL_REF)
    return 0;

  if (call_cookie & CALL_SHORT)
    return 0;

  if (TARGET_LONG_CALLS)
    {
      if (flag_function_sections
	  || DECL_SECTION_NAME (current_function_decl))
	/* c.3 is handled by the definition of the
	   ARM_DECLARE_FUNCTION_SIZE macro.  */
	return 1;
    }

  if (current_file_function_operand (sym_ref))
    return 0;

  return (call_cookie & CALL_LONG)
    || ENCODED_LONG_CALL_ATTR_P (XSTR (sym_ref, 0))
    || TARGET_LONG_CALLS;
}