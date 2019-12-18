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
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  omit_two_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (size_t const) ; 
 size_t strspn (char const*,char const*) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strspn (tree arglist)
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
	  const size_t r = strspn (p1, p2);
	  return size_int (r);
	}

      /* If either argument is "", return 0.  */
      if ((p1 && *p1 == '\0') || (p2 && *p2 == '\0'))
	/* Evaluate and ignore both arguments in case either one has
	   side-effects.  */
	return omit_two_operands (integer_type_node, integer_zero_node,
				  s1, s2);
      return 0;
    }
}