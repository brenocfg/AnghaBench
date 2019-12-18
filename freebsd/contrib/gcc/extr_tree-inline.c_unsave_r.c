#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  int /*<<< orphan*/  splay_tree ;
struct TYPE_6__ {int /*<<< orphan*/  decl_map; } ;
typedef  TYPE_2__ copy_body_data ;
struct TYPE_5__ {scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ BIND_EXPR ; 
 scalar_t__ LABEL_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SAVE_EXPR ; 
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STATIC (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  copy_bind_expr (scalar_t__*,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  copy_statement_list (scalar_t__*) ; 
 int /*<<< orphan*/  copy_tree_r (scalar_t__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remap_save_expr (scalar_t__*,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsave_expr_1 (scalar_t__) ; 

__attribute__((used)) static tree
unsave_r (tree *tp, int *walk_subtrees, void *data)
{
  copy_body_data *id = (copy_body_data *) data;
  splay_tree st = id->decl_map;
  splay_tree_node n;

  /* Only a local declaration (variable or label).  */
  if ((TREE_CODE (*tp) == VAR_DECL && !TREE_STATIC (*tp))
      || TREE_CODE (*tp) == LABEL_DECL)
    {
      /* Lookup the declaration.  */
      n = splay_tree_lookup (st, (splay_tree_key) *tp);

      /* If it's there, remap it.  */
      if (n)
	*tp = (tree) n->value;
    }

  else if (TREE_CODE (*tp) == STATEMENT_LIST)
    copy_statement_list (tp);
  else if (TREE_CODE (*tp) == BIND_EXPR)
    copy_bind_expr (tp, walk_subtrees, id);
  else if (TREE_CODE (*tp) == SAVE_EXPR)
    remap_save_expr (tp, st, walk_subtrees);
  else
    {
      copy_tree_r (tp, walk_subtrees, NULL);

      /* Do whatever unsaving is required.  */
      unsave_expr_1 (*tp);
    }

  /* Keep iterating.  */
  return NULL_TREE;
}