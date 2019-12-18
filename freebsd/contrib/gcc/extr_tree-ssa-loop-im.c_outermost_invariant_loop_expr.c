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
struct loop {int dummy; } ;
typedef  enum tree_code_class { ____Placeholder_tree_code_class } tree_code_class ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_CLASS (scalar_t__) ; 
 unsigned int TREE_CODE_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ flow_loop_nested_p (struct loop*,struct loop*) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 struct loop* outermost_invariant_loop (int /*<<< orphan*/ ,struct loop*) ; 
 struct loop* superloop_at_depth (struct loop*,int) ; 
 int tcc_binary ; 
 int tcc_comparison ; 
 int tcc_expression ; 
 int tcc_unary ; 

__attribute__((used)) static struct loop *
outermost_invariant_loop_expr (tree expr, struct loop *loop)
{
  enum tree_code_class class = TREE_CODE_CLASS (TREE_CODE (expr));
  unsigned i, nops;
  struct loop *max_loop = superloop_at_depth (loop, 1), *aloop;

  if (TREE_CODE (expr) == SSA_NAME
      || TREE_CODE (expr) == INTEGER_CST
      || is_gimple_min_invariant (expr))
    return outermost_invariant_loop (expr, loop);

  if (class != tcc_unary
      && class != tcc_binary
      && class != tcc_expression
      && class != tcc_comparison)
    return NULL;

  nops = TREE_CODE_LENGTH (TREE_CODE (expr));
  for (i = 0; i < nops; i++)
    {
      aloop = outermost_invariant_loop_expr (TREE_OPERAND (expr, i), loop);
      if (!aloop)
	return NULL;

      if (flow_loop_nested_p (max_loop, aloop))
	max_loop = aloop;
    }

  return max_loop;
}