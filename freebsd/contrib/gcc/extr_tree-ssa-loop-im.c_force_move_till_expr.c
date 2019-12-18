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
 scalar_t__ IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_CLASS (scalar_t__) ; 
 unsigned int TREE_CODE_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_level (int /*<<< orphan*/ ,struct loop*,struct loop*) ; 
 int tcc_binary ; 
 int tcc_comparison ; 
 int tcc_expression ; 
 int tcc_unary ; 

__attribute__((used)) static void
force_move_till_expr (tree expr, struct loop *orig_loop, struct loop *loop)
{
  enum tree_code_class class = TREE_CODE_CLASS (TREE_CODE (expr));
  unsigned i, nops;

  if (TREE_CODE (expr) == SSA_NAME)
    {
      tree stmt = SSA_NAME_DEF_STMT (expr);
      if (IS_EMPTY_STMT (stmt))
	return;

      set_level (stmt, orig_loop, loop);
      return;
    }

  if (class != tcc_unary
      && class != tcc_binary
      && class != tcc_expression
      && class != tcc_comparison)
    return;

  nops = TREE_CODE_LENGTH (TREE_CODE (expr));
  for (i = 0; i < nops; i++)
    force_move_till_expr (TREE_OPERAND (expr, i), orig_loop, loop);
}