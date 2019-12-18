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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;
struct walk_stmt_info {int /*<<< orphan*/  tsi; struct nesting_info* info; } ;
struct var_map_elt {int /*<<< orphan*/  new; int /*<<< orphan*/  old; } ;
struct nesting_info {int /*<<< orphan*/  var_map; } ;

/* Variables and functions */
 scalar_t__ GOTO_EXPR ; 
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 scalar_t__ block_may_fallthru (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct var_map_elt*) ; 
 scalar_t__ tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_link_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
convert_nl_goto_receiver (tree *tp, int *walk_subtrees, void *data)
{
  struct walk_stmt_info *wi = (struct walk_stmt_info *) data;
  struct nesting_info *info = wi->info;
  tree t = *tp, label, new_label, x;
  struct var_map_elt *elt, dummy;
  tree_stmt_iterator tmp_tsi;

  *walk_subtrees = 0;
  if (TREE_CODE (t) != LABEL_EXPR)
    return NULL_TREE;
  label = LABEL_EXPR_LABEL (t);

  dummy.old = label;
  elt = (struct var_map_elt *) htab_find (info->var_map, &dummy);
  if (!elt)
    return NULL_TREE;
  new_label = elt->new;

  /* If there's any possibility that the previous statement falls through,
     then we must branch around the new non-local label.  */
  tmp_tsi = wi->tsi;
  tsi_prev (&tmp_tsi);
  if (tsi_end_p (tmp_tsi) || block_may_fallthru (tsi_stmt (tmp_tsi)))
    {
      x = build1 (GOTO_EXPR, void_type_node, label);
      tsi_link_before (&wi->tsi, x, TSI_SAME_STMT);
    }
  x = build1 (LABEL_EXPR, void_type_node, new_label);
  tsi_link_before (&wi->tsi, x, TSI_SAME_STMT);

  return NULL_TREE;
}