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

/* Variables and functions */
 size_t BUILT_IN_STRCAT ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 scalar_t__ compare_tree_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omit_two_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strncat (tree arglist)
{
  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree dst = TREE_VALUE (arglist);
      tree src = TREE_VALUE (TREE_CHAIN (arglist));
      tree len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));
      const char *p = c_getstr (src);

      /* If the requested length is zero, or the src parameter string
	 length is zero, return the dst parameter.  */
      if (integer_zerop (len) || (p && *p == '\0'))
	return omit_two_operands (TREE_TYPE (dst), dst, src, len);

      /* If the requested len is greater than or equal to the string
	 length, call strcat.  */
      if (TREE_CODE (len) == INTEGER_CST && p
	  && compare_tree_int (len, strlen (p)) >= 0)
	{
	  tree newarglist
	    = tree_cons (NULL_TREE, dst, build_tree_list (NULL_TREE, src));
	  tree fn = implicit_built_in_decls[BUILT_IN_STRCAT];

	  /* If the replacement _DECL isn't initialized, don't do the
	     transformation.  */
	  if (!fn)
	    return 0;

	  return build_function_call_expr (fn, newarglist);
	}
      return 0;
    }
}