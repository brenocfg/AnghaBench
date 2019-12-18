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
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 int /*<<< orphan*/  COND_EXPR_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_dst_predicate_list (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_with_exit_edge_p (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extract_true_false_edges_from_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  invert_truthvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tree_if_convert_cond_expr (struct loop *loop, tree stmt, tree cond,
			   block_stmt_iterator *bsi)
{
  tree c, c2;
  edge true_edge, false_edge;

  gcc_assert (TREE_CODE (stmt) == COND_EXPR);

  c = COND_EXPR_COND (stmt);

  extract_true_false_edges_from_block (bb_for_stmt (stmt),
 				       &true_edge, &false_edge);

  /* Add new condition into destination's predicate list.  */

  /* If 'c' is true then TRUE_EDGE is taken.  */
  add_to_dst_predicate_list (loop, true_edge, cond,
			     unshare_expr (c), bsi);

  /* If 'c' is false then FALSE_EDGE is taken.  */
  c2 = invert_truthvalue (unshare_expr (c));
  add_to_dst_predicate_list (loop, false_edge, cond, c2, bsi);

  /* Now this conditional statement is redundant. Remove it.
     But, do not remove exit condition! Update exit condition
     using new condition.  */
  if (!bb_with_exit_edge_p (loop, bb_for_stmt (stmt)))
    {
      bsi_remove (bsi, true);
      cond = NULL_TREE;
    }
  return;
}