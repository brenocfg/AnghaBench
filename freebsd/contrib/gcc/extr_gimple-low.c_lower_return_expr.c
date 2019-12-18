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
typedef  scalar_t__ tree ;
struct lower_data {scalar_t__ return_statements; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_LOCUS (scalar_t__) ; 
 int /*<<< orphan*/  GOTO_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  SET_EXPR_LOCUS (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ create_artificial_label () ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tsi_delink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_link_before (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_return_expr (tree_stmt_iterator *tsi, struct lower_data *data)
{
  tree stmt = tsi_stmt (*tsi);
  tree value, t, label;

  /* Extract the value being returned.  */
  value = TREE_OPERAND (stmt, 0);
  if (value && TREE_CODE (value) == MODIFY_EXPR)
    value = TREE_OPERAND (value, 1);

  /* Match this up with an existing return statement that's been created.  */
  for (t = data->return_statements; t ; t = TREE_CHAIN (t))
    {
      tree tvalue = TREE_OPERAND (TREE_VALUE (t), 0);
      if (tvalue && TREE_CODE (tvalue) == MODIFY_EXPR)
	tvalue = TREE_OPERAND (tvalue, 1);

      if (value == tvalue)
	{
	  label = TREE_PURPOSE (t);
	  goto found;
	}
    }

  /* Not found.  Create a new label and record the return statement.  */
  label = create_artificial_label ();
  data->return_statements = tree_cons (label, stmt, data->return_statements);

  /* Generate a goto statement and remove the return statement.  */
 found:
  t = build1 (GOTO_EXPR, void_type_node, label);
  SET_EXPR_LOCUS (t, EXPR_LOCUS (stmt));
  tsi_link_before (tsi, t, TSI_SAME_STMT);
  tsi_delink (tsi);
}