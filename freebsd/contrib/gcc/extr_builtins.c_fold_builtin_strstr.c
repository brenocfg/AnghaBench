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
 size_t BUILT_IN_STRCHR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 char* strstr (char const*,char const*) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strstr (tree arglist, tree type)
{
  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree s1 = TREE_VALUE (arglist), s2 = TREE_VALUE (TREE_CHAIN (arglist));
      tree fn;
      const char *p1, *p2;

      p2 = c_getstr (s2);
      if (p2 == NULL)
	return 0;

      p1 = c_getstr (s1);
      if (p1 != NULL)
	{
	  const char *r = strstr (p1, p2);
	  tree tem;

	  if (r == NULL)
	    return build_int_cst (TREE_TYPE (s1), 0);

	  /* Return an offset into the constant string argument.  */
	  tem = fold_build2 (PLUS_EXPR, TREE_TYPE (s1),
			     s1, build_int_cst (TREE_TYPE (s1), r - p1));
	  return fold_convert (type, tem);
	}

      /* The argument is const char *, and the result is char *, so we need
	 a type conversion here to avoid a warning.  */
      if (p2[0] == '\0')
	return fold_convert (type, s1);

      if (p2[1] != '\0')
	return 0;

      fn = implicit_built_in_decls[BUILT_IN_STRCHR];
      if (!fn)
	return 0;

      /* New argument list transforming strstr(s1, s2) to
	 strchr(s1, s2[0]).  */
      arglist = build_tree_list (NULL_TREE,
				 build_int_cst (NULL_TREE, p2[0]));
      arglist = tree_cons (NULL_TREE, s1, arglist);
      return build_function_call_expr (fn, arglist);
    }
}