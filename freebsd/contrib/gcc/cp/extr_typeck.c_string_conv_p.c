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
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  OPT_Wwrite_strings ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ STRING_CST ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_QUAL_CONST ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_qualified_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wchar_type_node ; 

int
string_conv_p (tree totype, tree exp, int warn)
{
  tree t;

  if (TREE_CODE (totype) != POINTER_TYPE)
    return 0;

  t = TREE_TYPE (totype);
  if (!same_type_p (t, char_type_node)
      && !same_type_p (t, wchar_type_node))
    return 0;

  if (TREE_CODE (exp) == STRING_CST)
    {
      /* Make sure that we don't try to convert between char and wchar_t.  */
      if (!same_type_p (TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (exp))), t))
	return 0;
    }
  else
    {
      /* Is this a string constant which has decayed to 'const char *'?  */
      t = build_pointer_type (build_qualified_type (t, TYPE_QUAL_CONST));
      if (!same_type_p (TREE_TYPE (exp), t))
	return 0;
      STRIP_NOPS (exp);
      if (TREE_CODE (exp) != ADDR_EXPR
	  || TREE_CODE (TREE_OPERAND (exp, 0)) != STRING_CST)
	return 0;
    }

  /* This warning is not very useful, as it complains about printf.  */
  if (warn)
    warning (OPT_Wwrite_strings,
	     "deprecated conversion from string constant to %qT",
	     totype);

  return 1;
}