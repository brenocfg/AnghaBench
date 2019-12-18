#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  var_ann_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
struct TYPE_4__ {int has_volatile_ops; } ;

/* Variables and functions */
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 int SSA_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_virtual_operand (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  append_def (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int is_gimple_reg (int /*<<< orphan*/ ) ; 
 int opf_is_def ; 
 int /*<<< orphan*/  var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_stmt_operand (tree *var_p, stmt_ann_t s_ann, int flags)
{
  bool is_real_op;
  tree var, sym;
  var_ann_t v_ann;

  var = *var_p;
  gcc_assert (SSA_VAR_P (var));

  is_real_op = is_gimple_reg (var);

  /* If this is a real operand, the operand is either an SSA name or a 
     decl.  Virtual operands may only be decls.  */
  gcc_assert (is_real_op || DECL_P (var));

  sym = (TREE_CODE (var) == SSA_NAME ? SSA_NAME_VAR (var) : var);
  v_ann = var_ann (sym);

  /* Mark statements with volatile operands.  Optimizers should back
     off from statements having volatile operands.  */
  if (TREE_THIS_VOLATILE (sym) && s_ann)
    s_ann->has_volatile_ops = true;

  if (is_real_op)
    {
      /* The variable is a GIMPLE register.  Add it to real operands.  */
      if (flags & opf_is_def)
	append_def (var_p);
      else
	append_use (var_p);
    }
  else
    add_virtual_operand (var, s_ann, flags, NULL_TREE, 0, -1, false);
}