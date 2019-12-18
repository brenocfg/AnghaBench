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

/* Variables and functions */
 size_t BUILT_IN_FPUTC ; 
 size_t BUILT_IN_FPUTC_UNLOCKED ; 
 size_t BUILT_IN_FWRITE ; 
 size_t BUILT_IN_FWRITE_UNLOCKED ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,char const) ; 
 scalar_t__ build_tree_list (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* built_in_decls ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int /*<<< orphan*/ ) ; 
 int compare_tree_int (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__* implicit_built_in_decls ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  optimize_size ; 
 scalar_t__ size_one_node ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_builtin_fputs (tree arglist, bool ignore, bool unlocked, tree len)
{
  tree fn;
  /* If we're using an unlocked function, assume the other unlocked
     functions exist explicitly.  */
  tree const fn_fputc = unlocked ? built_in_decls[BUILT_IN_FPUTC_UNLOCKED]
    : implicit_built_in_decls[BUILT_IN_FPUTC];
  tree const fn_fwrite = unlocked ? built_in_decls[BUILT_IN_FWRITE_UNLOCKED]
    : implicit_built_in_decls[BUILT_IN_FWRITE];

  /* If the return value is used, don't do the transformation.  */
  if (!ignore)
    return 0;

  /* Verify the arguments in the original call.  */
  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;

  if (! len)
    len = c_strlen (TREE_VALUE (arglist), 0);

  /* Get the length of the string passed to fputs.  If the length
     can't be determined, punt.  */
  if (!len
      || TREE_CODE (len) != INTEGER_CST)
    return 0;

  switch (compare_tree_int (len, 1))
    {
    case -1: /* length is 0, delete the call entirely .  */
      return omit_one_operand (integer_type_node, integer_zero_node,
			       TREE_VALUE (TREE_CHAIN (arglist)));

    case 0: /* length is 1, call fputc.  */
      {
	const char *p = c_getstr (TREE_VALUE (arglist));

	if (p != NULL)
	  {
	    /* New argument list transforming fputs(string, stream) to
	       fputc(string[0], stream).  */
	    arglist = build_tree_list (NULL_TREE,
				       TREE_VALUE (TREE_CHAIN (arglist)));
	    arglist = tree_cons (NULL_TREE,
				 build_int_cst (NULL_TREE, p[0]),
				 arglist);
	    fn = fn_fputc;
	    break;
	  }
      }
      /* FALLTHROUGH */
    case 1: /* length is greater than 1, call fwrite.  */
      {
	tree string_arg;

	/* If optimizing for size keep fputs.  */
	if (optimize_size)
	  return 0;
	string_arg = TREE_VALUE (arglist);
	/* New argument list transforming fputs(string, stream) to
	   fwrite(string, 1, len, stream).  */
	arglist = build_tree_list (NULL_TREE,
				   TREE_VALUE (TREE_CHAIN (arglist)));
	arglist = tree_cons (NULL_TREE, len, arglist);
	arglist = tree_cons (NULL_TREE, size_one_node, arglist);
	arglist = tree_cons (NULL_TREE, string_arg, arglist);
	fn = fn_fwrite;
	break;
      }
    default:
      gcc_unreachable ();
    }

  /* If the replacement _DECL isn't initialized, don't do the
     transformation.  */
  if (!fn)
    return 0;

  /* These optimizations are only performed when the result is ignored,
     hence there's no need to cast the result to integer_type_node.  */
  return build_function_call_expr (fn, arglist);
}