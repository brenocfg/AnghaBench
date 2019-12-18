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
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ PHI_NODE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  degenerate_phi_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static tree
get_rhs_or_phi_arg (tree t)
{
  if (TREE_CODE (t) == PHI_NODE)
    return degenerate_phi_result (t);
  else if (TREE_CODE (t) == MODIFY_EXPR)
    return TREE_OPERAND (t, 1);
  gcc_unreachable ();
}