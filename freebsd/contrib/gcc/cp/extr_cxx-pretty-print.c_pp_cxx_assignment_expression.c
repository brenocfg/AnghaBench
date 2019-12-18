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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
#define  INIT_EXPR 131 
#define  MODIFY_EXPR 130 
#define  MODOP_EXPR 129 
#define  THROW_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_logical_or_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_assignment_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_conditional_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_equal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_assignment_expression (cxx_pretty_printer *pp, tree e)
{
  switch (TREE_CODE (e))
    {
    case MODIFY_EXPR:
    case INIT_EXPR:
      pp_c_logical_or_expression (pp_c_base (pp), TREE_OPERAND (e, 0));
      pp_space (pp);
      pp_equal (pp);
      pp_space (pp);
      pp_cxx_assignment_expression (pp, TREE_OPERAND (e, 1));
      break;

    case THROW_EXPR:
      pp_cxx_identifier (pp, "throw");
      if (TREE_OPERAND (e, 0))
	pp_cxx_assignment_expression (pp, TREE_OPERAND (e, 0));
      break;

    case MODOP_EXPR:
      pp_c_logical_or_expression (pp_c_base (pp), TREE_OPERAND (e, 0));
      pp_cxx_assignment_operator (pp, TREE_OPERAND (e, 1));
      pp_cxx_assignment_expression (pp, TREE_OPERAND (e, 2));
      break;

    default:
      pp_cxx_conditional_expression (pp, e);
      break;
    }
}