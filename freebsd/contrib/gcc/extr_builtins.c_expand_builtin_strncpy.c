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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BIGGEST_ALIGNMENT ; 
 scalar_t__ COMPOUND_EXPR ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_strncpy_read_str ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 int /*<<< orphan*/  can_store_by_pieces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_builtin_strncpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 
 int /*<<< orphan*/  get_memory_rtx (scalar_t__,scalar_t__) ; 
 unsigned int get_pointer_alignment (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 int /*<<< orphan*/  ptr_mode ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssize_int (int) ; 
 int /*<<< orphan*/  store_by_pieces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_low_cst (scalar_t__,int) ; 
 scalar_t__ validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_strncpy (tree exp, rtx target, enum machine_mode mode)
{
  tree fndecl = get_callee_fndecl (exp);
  tree arglist = TREE_OPERAND (exp, 1);
  if (validate_arglist (arglist,
			POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    {
      tree slen = c_strlen (TREE_VALUE (TREE_CHAIN (arglist)), 1);
      tree len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));
      tree result = fold_builtin_strncpy (fndecl, arglist, slen);

      if (result)
	{
	  while (TREE_CODE (result) == COMPOUND_EXPR)
	    {
	      expand_expr (TREE_OPERAND (result, 0), const0_rtx, VOIDmode,
			   EXPAND_NORMAL);
	      result = TREE_OPERAND (result, 1);
	    }
	  return expand_expr (result, target, mode, EXPAND_NORMAL);
	}

      /* We must be passed a constant len and src parameter.  */
      if (!host_integerp (len, 1) || !slen || !host_integerp (slen, 1))
	return 0;

      slen = size_binop (PLUS_EXPR, slen, ssize_int (1));

      /* We're required to pad with trailing zeros if the requested
	 len is greater than strlen(s2)+1.  In that case try to
	 use store_by_pieces, if it fails, punt.  */
      if (tree_int_cst_lt (slen, len))
	{
	  tree dest = TREE_VALUE (arglist);
	  unsigned int dest_align
	    = get_pointer_alignment (dest, BIGGEST_ALIGNMENT);
	  const char *p = c_getstr (TREE_VALUE (TREE_CHAIN (arglist)));
	  rtx dest_mem;

	  if (!p || dest_align == 0 || !host_integerp (len, 1)
	      || !can_store_by_pieces (tree_low_cst (len, 1),
				       builtin_strncpy_read_str,
				       (void *) p, dest_align))
	    return 0;

	  dest_mem = get_memory_rtx (dest, len);
	  store_by_pieces (dest_mem, tree_low_cst (len, 1),
			   builtin_strncpy_read_str,
			   (void *) p, dest_align, 0);
	  dest_mem = force_operand (XEXP (dest_mem, 0), NULL_RTX);
	  dest_mem = convert_memory_address (ptr_mode, dest_mem);
	  return dest_mem;
	}
    }
  return 0;
}