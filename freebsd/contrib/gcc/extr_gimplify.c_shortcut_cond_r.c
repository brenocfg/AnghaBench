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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUTH_ANDIF_EXPR ; 
 scalar_t__ TRUTH_ORIF_EXPR ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_and_jump (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
shortcut_cond_r (tree pred, tree *true_label_p, tree *false_label_p)
{
  tree local_label = NULL_TREE;
  tree t, expr = NULL;

  /* OK, it's not a simple case; we need to pull apart the COND_EXPR to
     retain the shortcut semantics.  Just insert the gotos here;
     shortcut_cond_expr will append the real blocks later.  */
  if (TREE_CODE (pred) == TRUTH_ANDIF_EXPR)
    {
      /* Turn if (a && b) into

	 if (a); else goto no;
	 if (b) goto yes; else goto no;
	 (no:) */

      if (false_label_p == NULL)
	false_label_p = &local_label;

      t = shortcut_cond_r (TREE_OPERAND (pred, 0), NULL, false_label_p);
      append_to_statement_list (t, &expr);

      t = shortcut_cond_r (TREE_OPERAND (pred, 1), true_label_p,
			   false_label_p);
      append_to_statement_list (t, &expr);
    }
  else if (TREE_CODE (pred) == TRUTH_ORIF_EXPR)
    {
      /* Turn if (a || b) into

	 if (a) goto yes;
	 if (b) goto yes; else goto no;
	 (yes:) */

      if (true_label_p == NULL)
	true_label_p = &local_label;

      t = shortcut_cond_r (TREE_OPERAND (pred, 0), true_label_p, NULL);
      append_to_statement_list (t, &expr);

      t = shortcut_cond_r (TREE_OPERAND (pred, 1), true_label_p,
			   false_label_p);
      append_to_statement_list (t, &expr);
    }
  else if (TREE_CODE (pred) == COND_EXPR)
    {
      /* As long as we're messing with gotos, turn if (a ? b : c) into
	 if (a)
	   if (b) goto yes; else goto no;
	 else
	   if (c) goto yes; else goto no;  */
      expr = build3 (COND_EXPR, void_type_node, TREE_OPERAND (pred, 0),
		     shortcut_cond_r (TREE_OPERAND (pred, 1), true_label_p,
				      false_label_p),
		     shortcut_cond_r (TREE_OPERAND (pred, 2), true_label_p,
				      false_label_p));
    }
  else
    {
      expr = build3 (COND_EXPR, void_type_node, pred,
		     build_and_jump (true_label_p),
		     build_and_jump (false_label_p));
    }

  if (local_label)
    {
      t = build1 (LABEL_EXPR, void_type_node, local_label);
      append_to_statement_list (t, &expr);
    }

  return expr;
}