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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 size_t BUILT_IN_MEMCPY ; 
#define  BUILT_IN_MEMCPY_CHK 131 
 size_t BUILT_IN_MEMMOVE ; 
#define  BUILT_IN_MEMMOVE_CHK 130 
 size_t BUILT_IN_MEMPCPY ; 
#define  BUILT_IN_MEMPCPY_CHK 129 
 size_t BUILT_IN_MEMSET ; 
#define  BUILT_IN_MEMSET_CHK 128 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__* built_in_decls ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 int /*<<< orphan*/  integer_all_onesp (scalar_t__) ; 
 scalar_t__ omit_one_operand (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_builtin_memory_chk (tree fndecl, tree arglist, tree maxlen, bool ignore,
			 enum built_in_function fcode)
{
  tree dest, src, len, size, fn;

  if (!validate_arglist (arglist,
			 POINTER_TYPE,
			 fcode == BUILT_IN_MEMSET_CHK
			 ? INTEGER_TYPE : POINTER_TYPE,
			 INTEGER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;

  dest = TREE_VALUE (arglist);
  /* Actually val for __memset_chk, but it doesn't matter.  */
  src = TREE_VALUE (TREE_CHAIN (arglist));
  len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));
  size = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (TREE_CHAIN (arglist))));

  /* If SRC and DEST are the same (and not volatile), return DEST
     (resp. DEST+LEN for __mempcpy_chk).  */
  if (fcode != BUILT_IN_MEMSET_CHK && operand_equal_p (src, dest, 0))
    {
      if (fcode != BUILT_IN_MEMPCPY_CHK)
	return omit_one_operand (TREE_TYPE (TREE_TYPE (fndecl)), dest, len);
      else
	{
	  tree temp = fold_convert (TREE_TYPE (dest), len);
	  temp = fold_build2 (PLUS_EXPR, TREE_TYPE (dest), dest, temp);
	  return fold_convert (TREE_TYPE (TREE_TYPE (fndecl)), temp);
	}
    }

  if (! host_integerp (size, 1))
    return 0;

  if (! integer_all_onesp (size))
    {
      if (! host_integerp (len, 1))
	{
	  /* If LEN is not constant, try MAXLEN too.
	     For MAXLEN only allow optimizing into non-_ocs function
	     if SIZE is >= MAXLEN, never convert to __ocs_fail ().  */
	  if (maxlen == NULL_TREE || ! host_integerp (maxlen, 1))
	    {
	      if (fcode == BUILT_IN_MEMPCPY_CHK && ignore)
		{
		  /* (void) __mempcpy_chk () can be optimized into
		     (void) __memcpy_chk ().  */
		  fn = built_in_decls[BUILT_IN_MEMCPY_CHK];
		  if (!fn)
		    return 0;

		  return build_function_call_expr (fn, arglist);
		}
	      return 0;
	    }
	}
      else
	maxlen = len;

      if (tree_int_cst_lt (size, maxlen))
	return 0;
    }

  arglist = build_tree_list (NULL_TREE, len);
  arglist = tree_cons (NULL_TREE, src, arglist);
  arglist = tree_cons (NULL_TREE, dest, arglist);

  fn = NULL_TREE;
  /* If __builtin_mem{cpy,pcpy,move,set}_chk is used, assume
     mem{cpy,pcpy,move,set} is available.  */
  switch (fcode)
    {
    case BUILT_IN_MEMCPY_CHK:
      fn = built_in_decls[BUILT_IN_MEMCPY];
      break;
    case BUILT_IN_MEMPCPY_CHK:
      fn = built_in_decls[BUILT_IN_MEMPCPY];
      break;
    case BUILT_IN_MEMMOVE_CHK:
      fn = built_in_decls[BUILT_IN_MEMMOVE];
      break;
    case BUILT_IN_MEMSET_CHK:
      fn = built_in_decls[BUILT_IN_MEMSET];
      break;
    default:
      break;
    }

  if (!fn)
    return 0;

  return build_function_call_expr (fn, arglist);
}