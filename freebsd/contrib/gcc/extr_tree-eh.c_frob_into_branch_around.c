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

/* Variables and functions */
 int /*<<< orphan*/  GOTO_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  append_to_statement_list (scalar_t__,scalar_t__*) ; 
 scalar_t__ block_may_fallthru (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ create_artificial_label () ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
frob_into_branch_around (tree *tp, tree lab, tree over)
{
  tree x, op1;

  op1 = TREE_OPERAND (*tp, 1);
  *tp = TREE_OPERAND (*tp, 0);

  if (block_may_fallthru (*tp))
    {
      if (!over)
	over = create_artificial_label ();
      x = build1 (GOTO_EXPR, void_type_node, over);
      append_to_statement_list (x, tp);
    }

  if (lab)
    {
      x = build1 (LABEL_EXPR, void_type_node, lab);
      append_to_statement_list (x, tp);
    }

  append_to_statement_list (op1, tp);

  if (over)
    {
      x = build1 (LABEL_EXPR, void_type_node, over);
      append_to_statement_list (x, tp);
    }
}