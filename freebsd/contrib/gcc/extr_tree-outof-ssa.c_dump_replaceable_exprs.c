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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ SINGLE_SSA_TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_OP_DEF ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ num_ssa_names ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_replaceable_exprs (FILE *f, tree *expr)
{
  tree stmt, var;
  int x;
  fprintf (f, "\nReplacing Expressions\n");
  for (x = 0; x < (int)num_ssa_names + 1; x++)
    if (expr[x])
      {
        stmt = expr[x];
	var = SINGLE_SSA_TREE_OPERAND (stmt, SSA_OP_DEF);
	gcc_assert (var != NULL_TREE);
	print_generic_expr (f, var, TDF_SLIM);
	fprintf (f, " replace with --> ");
	print_generic_expr (f, TREE_OPERAND (stmt, 1), TDF_SLIM);
	fprintf (f, "\n");
      }
  fprintf (f, "\n");
}