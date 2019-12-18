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
 int /*<<< orphan*/  building_stmt_tree () ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_stmt_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static tree
finish_init_stmts (bool is_global, tree stmt_expr, tree compound_stmt)
{
  finish_compound_stmt (compound_stmt);

  stmt_expr = finish_stmt_expr (stmt_expr, true);

  gcc_assert (!building_stmt_tree () == is_global);

  return stmt_expr;
}