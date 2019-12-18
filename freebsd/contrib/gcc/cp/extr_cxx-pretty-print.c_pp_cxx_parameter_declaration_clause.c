#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  cxx_pretty_printer ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/ * FUNCTION_FIRST_USER_PARM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FUNCTION_FIRST_USER_PARMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ METHOD_TYPE ; 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_PURPOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_ARG_TYPES (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* pp_c_base (int /*<<< orphan*/ *) ; 
 int pp_c_flag_abstract ; 
 int /*<<< orphan*/  pp_cxx_assignment_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pp_cxx_flag_default_argument ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_parameter_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_equal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_parameter_declaration_clause (cxx_pretty_printer *pp, tree t)
{
  tree args = TYPE_P (t) ? NULL : FUNCTION_FIRST_USER_PARM (t);
  tree types =
    TYPE_P (t) ? TYPE_ARG_TYPES (t) : FUNCTION_FIRST_USER_PARMTYPE (t);
  const bool abstract = args == NULL
    || pp_c_base (pp)->flags & pp_c_flag_abstract;
  bool first = true;

  /* Skip artificial parameter for nonstatic member functions.  */
  if (TREE_CODE (t) == METHOD_TYPE)
    types = TREE_CHAIN (types);

  pp_cxx_left_paren (pp);
  for (; args; args = TREE_CHAIN (args), types = TREE_CHAIN (types))
    {
      if (!first)
	pp_cxx_separate_with (pp, ',');
      first = false;
      pp_cxx_parameter_declaration (pp, abstract ? TREE_VALUE (types) : args);
      if (!abstract && pp_c_base (pp)->flags & pp_cxx_flag_default_argument)
	{
	  pp_cxx_whitespace (pp);
	  pp_equal (pp);
	  pp_cxx_whitespace (pp);
	  pp_cxx_assignment_expression (pp, TREE_PURPOSE (types));
	}
    }
  pp_cxx_right_paren (pp);
}