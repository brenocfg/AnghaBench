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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  COND_EXPR 133 
 int /*<<< orphan*/  COND_EXPR_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GOTO_DESTINATION (int /*<<< orphan*/ ) ; 
#define  GOTO_EXPR 132 
#define  LABEL_EXPR 131 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (int /*<<< orphan*/ ) ; 
#define  MODIFY_EXPR 130 
#define  RETURN_EXPR 129 
 int /*<<< orphan*/  SWITCH_COND (int /*<<< orphan*/ ) ; 
#define  SWITCH_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int WITH_SIZE_EXPR ; 

tree
get_rhs (tree stmt)
{
  enum tree_code code = TREE_CODE (stmt);

  switch (code)
    {
    case RETURN_EXPR:
      stmt = TREE_OPERAND (stmt, 0);
      if (!stmt || TREE_CODE (stmt) != MODIFY_EXPR)
	return stmt;
      /* FALLTHRU */

    case MODIFY_EXPR:
      stmt = TREE_OPERAND (stmt, 1);
      if (TREE_CODE (stmt) == WITH_SIZE_EXPR)
	return TREE_OPERAND (stmt, 0);
      else
	return stmt;

    case COND_EXPR:
      return COND_EXPR_COND (stmt);
    case SWITCH_EXPR:
      return SWITCH_COND (stmt);
    case GOTO_EXPR:
      return GOTO_DESTINATION (stmt);
    case LABEL_EXPR:
      return LABEL_EXPR_LABEL (stmt);

    default:
      return stmt;
    }
}