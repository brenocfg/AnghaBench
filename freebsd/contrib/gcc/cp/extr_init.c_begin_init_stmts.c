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

/* Variables and functions */
 int /*<<< orphan*/  BCS_NO_SCOPE ; 
 int /*<<< orphan*/  begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_stmt_expr () ; 
 int /*<<< orphan*/  building_stmt_tree () ; 

__attribute__((used)) static bool
begin_init_stmts (tree *stmt_expr_p, tree *compound_stmt_p)
{
  bool is_global = !building_stmt_tree ();

  *stmt_expr_p = begin_stmt_expr ();
  *compound_stmt_p = begin_compound_stmt (BCS_NO_SCOPE);

  return is_global;
}