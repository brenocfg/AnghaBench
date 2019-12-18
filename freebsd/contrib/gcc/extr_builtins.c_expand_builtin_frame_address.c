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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 scalar_t__ BUILT_IN_FRAME_ADDRESS ; 
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_FUNCTION_CODE (scalar_t__) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/ * const0_rtx ; 
 int /*<<< orphan*/ * copy_to_mode_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * expand_builtin_return_addr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_low_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static rtx
expand_builtin_frame_address (tree fndecl, tree arglist)
{
  /* The argument must be a nonnegative integer constant.
     It counts the number of frames to scan up the stack.
     The value is the return address saved in that frame.  */
  if (arglist == 0)
    /* Warning about missing arg was already issued.  */
    return const0_rtx;
  else if (! host_integerp (TREE_VALUE (arglist), 1))
    {
      if (DECL_FUNCTION_CODE (fndecl) == BUILT_IN_FRAME_ADDRESS)
	error ("invalid argument to %<__builtin_frame_address%>");
      else
	error ("invalid argument to %<__builtin_return_address%>");
      return const0_rtx;
    }
  else
    {
      rtx tem
	= expand_builtin_return_addr (DECL_FUNCTION_CODE (fndecl),
				      tree_low_cst (TREE_VALUE (arglist), 1));

      /* Some ports cannot access arbitrary stack frames.  */
      if (tem == NULL)
	{
	  if (DECL_FUNCTION_CODE (fndecl) == BUILT_IN_FRAME_ADDRESS)
	    warning (0, "unsupported argument to %<__builtin_frame_address%>");
	  else
	    warning (0, "unsupported argument to %<__builtin_return_address%>");
	  return const0_rtx;
	}

      /* For __builtin_frame_address, return what we've got.  */
      if (DECL_FUNCTION_CODE (fndecl) == BUILT_IN_FRAME_ADDRESS)
	return tem;

      if (!REG_P (tem)
	  && ! CONSTANT_P (tem))
	tem = copy_to_mode_reg (Pmode, tem);
      return tem;
    }
}