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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_RTL_SET_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  diddle_return_value (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_clobber_return_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
clobber_return_register (void)
{
  diddle_return_value (do_clobber_return_reg, NULL);

  /* In case we do use pseudo to return value, clobber it too.  */
  if (DECL_RTL_SET_P (DECL_RESULT (current_function_decl)))
    {
      tree decl_result = DECL_RESULT (current_function_decl);
      rtx decl_rtl = DECL_RTL (decl_result);
      if (REG_P (decl_rtl) && REGNO (decl_rtl) >= FIRST_PSEUDO_REGISTER)
	{
	  do_clobber_return_reg (decl_rtl, NULL);
	}
    }
}