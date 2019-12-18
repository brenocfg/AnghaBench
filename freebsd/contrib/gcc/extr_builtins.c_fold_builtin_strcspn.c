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
 size_t BUILT_IN_STRLEN ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (size_t const) ; 
 size_t strcspn (char const*,char const*) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strcspn (tree arglist)
{
  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree s1 = TREE_VALUE (arglist), s2 = TREE_VALUE (TREE_CHAIN (arglist));
      const char *p1 = c_getstr (s1), *p2 = c_getstr (s2);

      /* If both arguments are constants, evaluate at compile-time.  */
      if (p1 && p2)
	{
	  const size_t r = strcspn (p1, p2);
	  return size_int (r);
	}

      /* If the first argument is "", return 0.  */
      if (p1 && *p1 == '\0')
	{
	  /* Evaluate and ignore argument s2 in case it has
	     side-effects.  */
	  return omit_one_operand (integer_type_node,
				   integer_zero_node, s2);
	}

      /* If the second argument is "", return __builtin_strlen(s1).  */
      if (p2 && *p2 == '\0')
	{
	  tree newarglist = build_tree_list (NULL_TREE, s1),
	    fn = implicit_built_in_decls[BUILT_IN_STRLEN];

	  /* If the replacement _DECL isn't initialized, don't do the
	     transformation.  */
	  if (!fn)
	    return 0;

	  return build_function_call_expr (fn, newarglist);
	}
      return 0;
    }
}