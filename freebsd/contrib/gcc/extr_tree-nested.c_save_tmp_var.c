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
struct nesting_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_LOCUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  SET_EXPR_LOCUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmp_var_for (struct nesting_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_link_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
save_tmp_var (struct nesting_info *info, tree exp,
	      tree_stmt_iterator *tsi)
{
  tree t, stmt;

  t = create_tmp_var_for (info, TREE_TYPE (exp), NULL);
  stmt = build2 (MODIFY_EXPR, TREE_TYPE (t), exp, t);
  SET_EXPR_LOCUS (stmt, EXPR_LOCUS (tsi_stmt (*tsi)));
  tsi_link_after (tsi, stmt, TSI_SAME_STMT);

  return t;
}