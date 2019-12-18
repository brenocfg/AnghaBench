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
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  check_function_parameter_and_return_types (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  has_proper_scope_for_analysis (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_operand (tree t)
{
  if (!t) return;

  /* This is an assignment from a function, register the types as
     escaping.  */
  if (TREE_CODE (t) == FUNCTION_DECL)
    check_function_parameter_and_return_types (t, true);

  else if (TREE_CODE (t) == VAR_DECL)
    has_proper_scope_for_analysis (t); 
}