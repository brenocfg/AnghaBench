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
 scalar_t__ COND_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_logical_or_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_assignment_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_question (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_conditional_expression (cxx_pretty_printer *pp, tree e)
{
  if (TREE_CODE (e) == COND_EXPR)
    {
      pp_c_logical_or_expression (pp_c_base (pp), TREE_OPERAND (e, 0));
      pp_space (pp);
      pp_question (pp);
      pp_space (pp);
      pp_cxx_expression (pp, TREE_OPERAND (e, 1));
      pp_space (pp);
      pp_cxx_assignment_expression (pp, TREE_OPERAND (e, 2));
    }
  else
    pp_c_logical_or_expression (pp_c_base (pp), e);
}