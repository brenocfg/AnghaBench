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
typedef  int /*<<< orphan*/  splay_tree_value ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  int /*<<< orphan*/  splay_tree ;

/* Variables and functions */
 scalar_t__ AGGR_INIT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TARGET_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  break_out_target_exprs (scalar_t__) ; 
 scalar_t__ build_cplus_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_target_expr_with_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_tree_r (scalar_t__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
bot_manip (tree* tp, int* walk_subtrees, void* data)
{
  splay_tree target_remap = ((splay_tree) data);
  tree t = *tp;

  if (!TYPE_P (t) && TREE_CONSTANT (t))
    {
      /* There can't be any TARGET_EXPRs or their slot variables below
	 this point.  We used to check !TREE_SIDE_EFFECTS, but then we
	 failed to copy an ADDR_EXPR of the slot VAR_DECL.  */
      *walk_subtrees = 0;
      return NULL_TREE;
    }
  if (TREE_CODE (t) == TARGET_EXPR)
    {
      tree u;

      if (TREE_CODE (TREE_OPERAND (t, 1)) == AGGR_INIT_EXPR)
	u = build_cplus_new
	  (TREE_TYPE (t), break_out_target_exprs (TREE_OPERAND (t, 1)));
      else
	u = build_target_expr_with_type
	  (break_out_target_exprs (TREE_OPERAND (t, 1)), TREE_TYPE (t));

      /* Map the old variable to the new one.  */
      splay_tree_insert (target_remap,
			 (splay_tree_key) TREE_OPERAND (t, 0),
			 (splay_tree_value) TREE_OPERAND (u, 0));

      /* Replace the old expression with the new version.  */
      *tp = u;
      /* We don't have to go below this point; the recursive call to
	 break_out_target_exprs will have handled anything below this
	 point.  */
      *walk_subtrees = 0;
      return NULL_TREE;
    }

  /* Make a copy of this node.  */
  return copy_tree_r (tp, walk_subtrees, NULL);
}