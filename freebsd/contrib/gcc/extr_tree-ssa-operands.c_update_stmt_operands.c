#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
struct TYPE_3__ {int modified; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSA_VAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_TREE_OPS ; 
 int /*<<< orphan*/  build_ssa_operands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_stmt_ann (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssa_operands_active () ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
update_stmt_operands (tree stmt)
{
  stmt_ann_t ann = get_stmt_ann (stmt);

  /* If update_stmt_operands is called before SSA is initialized, do
     nothing.  */
  if (!ssa_operands_active ())
    return;

  /* The optimizers cannot handle statements that are nothing but a
     _DECL.  This indicates a bug in the gimplifier.  */
  gcc_assert (!SSA_VAR_P (stmt));

  gcc_assert (ann->modified);

  timevar_push (TV_TREE_OPS);

  build_ssa_operands (stmt);

  /* Clear the modified bit for STMT.  */
  ann->modified = 0;

  timevar_pop (TV_TREE_OPS);
}