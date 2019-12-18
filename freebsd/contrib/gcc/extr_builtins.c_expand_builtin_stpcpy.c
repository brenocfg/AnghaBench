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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 size_t BUILT_IN_STRCPY ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_strlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_builtin_mempcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ expand_builtin_strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ expand_expr (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_movstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_lowpart (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  get_callee_fndecl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 scalar_t__ plus_constant (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssize_int (int) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_stpcpy (tree exp, rtx target, enum machine_mode mode)
{
  tree arglist = TREE_OPERAND (exp, 1);
  /* If return value is ignored, transform stpcpy into strcpy.  */
  if (target == const0_rtx)
    {
      tree fn = implicit_built_in_decls[BUILT_IN_STRCPY];
      if (!fn)
	return 0;

      return expand_expr (build_function_call_expr (fn, arglist),
			  target, mode, EXPAND_NORMAL);
    }

  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree dst, src, len, lenp1;
      tree narglist;
      rtx ret;

      /* Ensure we get an actual string whose length can be evaluated at
	 compile-time, not an expression containing a string.  This is
	 because the latter will potentially produce pessimized code
	 when used to produce the return value.  */
      src = TREE_VALUE (TREE_CHAIN (arglist));
      if (! c_getstr (src) || ! (len = c_strlen (src, 0)))
	return expand_movstr (TREE_VALUE (arglist),
			      TREE_VALUE (TREE_CHAIN (arglist)),
			      target, /*endp=*/2);

      dst = TREE_VALUE (arglist);
      lenp1 = size_binop (PLUS_EXPR, len, ssize_int (1));
      narglist = build_tree_list (NULL_TREE, lenp1);
      narglist = tree_cons (NULL_TREE, src, narglist);
      narglist = tree_cons (NULL_TREE, dst, narglist);
      ret = expand_builtin_mempcpy (narglist, TREE_TYPE (exp),
				    target, mode, /*endp=*/2);

      if (ret)
	return ret;

      if (TREE_CODE (len) == INTEGER_CST)
	{
	  rtx len_rtx = expand_normal (len);

	  if (GET_CODE (len_rtx) == CONST_INT)
	    {
	      ret = expand_builtin_strcpy (get_callee_fndecl (exp),
					   arglist, target, mode);

	      if (ret)
		{
		  if (! target)
		    {
		      if (mode != VOIDmode)
			target = gen_reg_rtx (mode);
		      else
			target = gen_reg_rtx (GET_MODE (ret));
		    }
		  if (GET_MODE (target) != GET_MODE (ret))
		    ret = gen_lowpart (GET_MODE (target), ret);

		  ret = plus_constant (ret, INTVAL (len_rtx));
		  ret = emit_move_insn (target, force_operand (ret, NULL_RTX));
		  gcc_assert (ret);

		  return target;
		}
	    }
	}

      return expand_movstr (TREE_VALUE (arglist),
			    TREE_VALUE (TREE_CHAIN (arglist)),
			    target, /*endp=*/2);
    }
}