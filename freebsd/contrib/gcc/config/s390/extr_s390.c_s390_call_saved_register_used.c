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
typedef  int tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  CUMULATIVE_ARGS ;

/* Variables and functions */
 scalar_t__ ERROR_MARK ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int HARD_REGNO_NREGS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_CUMULATIVE_ARGS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Pmode ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int TREE_CHAIN (int) ; 
 scalar_t__ TREE_CODE (int) ; 
 int TREE_TYPE (int) ; 
 int TREE_VALUE (int) ; 
 int TYPE_MODE (int) ; 
 int build_pointer_type (int) ; 
 int /*<<< orphan*/ * call_used_regs ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ pass_by_reference (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  s390_function_arg (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_function_arg_advance (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
s390_call_saved_register_used (tree argument_list)
{
  CUMULATIVE_ARGS cum;
  tree parameter;
  enum machine_mode mode;
  tree type;
  rtx parm_rtx;
  int reg;

  INIT_CUMULATIVE_ARGS (cum, NULL, NULL, 0, 0);

  while (argument_list)
    {
      parameter = TREE_VALUE (argument_list);
      argument_list = TREE_CHAIN (argument_list);

      gcc_assert (parameter);

      /* For an undeclared variable passed as parameter we will get
	 an ERROR_MARK node here.  */
      if (TREE_CODE (parameter) == ERROR_MARK)
	return true;

      type = TREE_TYPE (parameter);
      gcc_assert (type);

      mode = TYPE_MODE (type);
      gcc_assert (mode);

      if (pass_by_reference (&cum, mode, type, true))
 	{
 	  mode = Pmode;
 	  type = build_pointer_type (type);
 	}

       parm_rtx = s390_function_arg (&cum, mode, type, 0);

       s390_function_arg_advance (&cum, mode, type, 0);

       if (parm_rtx && REG_P (parm_rtx))
	 {
	   for (reg = 0;
		reg < HARD_REGNO_NREGS (REGNO (parm_rtx), GET_MODE (parm_rtx));
		reg++)
	     if (! call_used_regs[reg + REGNO (parm_rtx)])
	       return true;
	 }
    }
  return false;
}