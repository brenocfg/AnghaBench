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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_SAVED_TREE (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_PARMS (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ most_general_template (scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_function_definition (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_simple_declaration (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_template_parameter_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_maybe_newline_and_indent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_newline_and_indent (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pp_cxx_template_declaration (cxx_pretty_printer *pp, tree t)
{
  tree tmpl = most_general_template (t);
  tree level;
  int i = 0;

  pp_maybe_newline_and_indent (pp, 0);
  for (level = DECL_TEMPLATE_PARMS (tmpl); level; level = TREE_CHAIN (level))
    {
      pp_cxx_identifier (pp, "template");
      pp_cxx_begin_template_argument_list (pp);
      pp_cxx_template_parameter_list (pp, TREE_VALUE (level));
      pp_cxx_end_template_argument_list (pp);
      pp_newline_and_indent (pp, 3);
      i += 3;
    }
  if (TREE_CODE (t) == FUNCTION_DECL && DECL_SAVED_TREE (t))
    pp_cxx_function_definition (pp, t);
  else
    pp_cxx_simple_declaration (pp, t);
}