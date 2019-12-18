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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
#define  BUILT_IN_FPUTS 141 
#define  BUILT_IN_FPUTS_UNLOCKED 140 
 scalar_t__ BUILT_IN_MD ; 
#define  BUILT_IN_MEMCPY_CHK 139 
#define  BUILT_IN_MEMMOVE_CHK 138 
#define  BUILT_IN_MEMPCPY_CHK 137 
#define  BUILT_IN_MEMSET_CHK 136 
#define  BUILT_IN_SNPRINTF_CHK 135 
#define  BUILT_IN_STPCPY_CHK 134 
#define  BUILT_IN_STRCPY 133 
#define  BUILT_IN_STRCPY_CHK 132 
#define  BUILT_IN_STRLEN 131 
#define  BUILT_IN_STRNCPY 130 
#define  BUILT_IN_STRNCPY_CHK 129 
#define  BUILT_IN_VSNPRINTF_CHK 128 
 scalar_t__ DECL_BUILT_IN_CLASS (scalar_t__) ; 
 int DECL_FUNCTION_CODE (scalar_t__) ; 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ fold_builtin (scalar_t__,scalar_t__,int) ; 
 scalar_t__ fold_builtin_fputs (scalar_t__,int,int,scalar_t__) ; 
 scalar_t__ fold_builtin_memory_chk (scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ fold_builtin_snprintf_chk (scalar_t__,scalar_t__,int) ; 
 scalar_t__ fold_builtin_strcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_builtin_strncpy (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_builtin_strncpy_chk (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_builtin_stxcpy_chk (scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fold_ignored_result (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 
 int /*<<< orphan*/  get_maxval_strlen (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_gimple_cast (scalar_t__) ; 
 int /*<<< orphan*/  is_gimple_val (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
ccp_fold_builtin (tree stmt, tree fn)
{
  tree result, val[3];
  tree callee, arglist, a;
  int arg_mask, i, type;
  bitmap visited;
  bool ignore;

  ignore = TREE_CODE (stmt) != MODIFY_EXPR;

  /* First try the generic builtin folder.  If that succeeds, return the
     result directly.  */
  callee = get_callee_fndecl (fn);
  arglist = TREE_OPERAND (fn, 1);
  result = fold_builtin (callee, arglist, ignore);
  if (result)
    {
      if (ignore)
	STRIP_NOPS (result);
      return result;
    }

  /* Ignore MD builtins.  */
  if (DECL_BUILT_IN_CLASS (callee) == BUILT_IN_MD)
    return NULL_TREE;

  /* If the builtin could not be folded, and it has no argument list,
     we're done.  */
  if (!arglist)
    return NULL_TREE;

  /* Limit the work only for builtins we know how to simplify.  */
  switch (DECL_FUNCTION_CODE (callee))
    {
    case BUILT_IN_STRLEN:
    case BUILT_IN_FPUTS:
    case BUILT_IN_FPUTS_UNLOCKED:
      arg_mask = 1;
      type = 0;
      break;
    case BUILT_IN_STRCPY:
    case BUILT_IN_STRNCPY:
      arg_mask = 2;
      type = 0;
      break;
    case BUILT_IN_MEMCPY_CHK:
    case BUILT_IN_MEMPCPY_CHK:
    case BUILT_IN_MEMMOVE_CHK:
    case BUILT_IN_MEMSET_CHK:
    case BUILT_IN_STRNCPY_CHK:
      arg_mask = 4;
      type = 2;
      break;
    case BUILT_IN_STRCPY_CHK:
    case BUILT_IN_STPCPY_CHK:
      arg_mask = 2;
      type = 1;
      break;
    case BUILT_IN_SNPRINTF_CHK:
    case BUILT_IN_VSNPRINTF_CHK:
      arg_mask = 2;
      type = 2;
      break;
    default:
      return NULL_TREE;
    }

  /* Try to use the dataflow information gathered by the CCP process.  */
  visited = BITMAP_ALLOC (NULL);

  memset (val, 0, sizeof (val));
  for (i = 0, a = arglist;
       arg_mask;
       i++, arg_mask >>= 1, a = TREE_CHAIN (a))
    if (arg_mask & 1)
      {
	bitmap_clear (visited);
	if (!get_maxval_strlen (TREE_VALUE (a), &val[i], visited, type))
	  val[i] = NULL_TREE;
      }

  BITMAP_FREE (visited);

  result = NULL_TREE;
  switch (DECL_FUNCTION_CODE (callee))
    {
    case BUILT_IN_STRLEN:
      if (val[0])
	{
	  tree new = fold_convert (TREE_TYPE (fn), val[0]);

	  /* If the result is not a valid gimple value, or not a cast
	     of a valid gimple value, then we can not use the result.  */
	  if (is_gimple_val (new)
	      || (is_gimple_cast (new)
		  && is_gimple_val (TREE_OPERAND (new, 0))))
	    return new;
	}
      break;

    case BUILT_IN_STRCPY:
      if (val[1] && is_gimple_val (val[1]))
	result = fold_builtin_strcpy (callee, arglist, val[1]);
      break;

    case BUILT_IN_STRNCPY:
      if (val[1] && is_gimple_val (val[1]))
	result = fold_builtin_strncpy (callee, arglist, val[1]);
      break;

    case BUILT_IN_FPUTS:
      result = fold_builtin_fputs (arglist,
				   TREE_CODE (stmt) != MODIFY_EXPR, 0,
				   val[0]);
      break;

    case BUILT_IN_FPUTS_UNLOCKED:
      result = fold_builtin_fputs (arglist,
				   TREE_CODE (stmt) != MODIFY_EXPR, 1,
				   val[0]);
      break;

    case BUILT_IN_MEMCPY_CHK:
    case BUILT_IN_MEMPCPY_CHK:
    case BUILT_IN_MEMMOVE_CHK:
    case BUILT_IN_MEMSET_CHK:
      if (val[2] && is_gimple_val (val[2]))
	result = fold_builtin_memory_chk (callee, arglist, val[2], ignore,
					  DECL_FUNCTION_CODE (callee));
      break;

    case BUILT_IN_STRCPY_CHK:
    case BUILT_IN_STPCPY_CHK:
      if (val[1] && is_gimple_val (val[1]))
	result = fold_builtin_stxcpy_chk (callee, arglist, val[1], ignore,
					  DECL_FUNCTION_CODE (callee));
      break;

    case BUILT_IN_STRNCPY_CHK:
      if (val[2] && is_gimple_val (val[2]))
	result = fold_builtin_strncpy_chk (arglist, val[2]);
      break;

    case BUILT_IN_SNPRINTF_CHK:
    case BUILT_IN_VSNPRINTF_CHK:
      if (val[1] && is_gimple_val (val[1]))
	result = fold_builtin_snprintf_chk (arglist, val[1],
					    DECL_FUNCTION_CODE (callee));
      break;

    default:
      gcc_unreachable ();
    }

  if (result && ignore)
    result = fold_ignored_result (result);
  return result;
}