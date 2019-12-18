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
typedef  TYPE_1__* var_ann_t ;
typedef  int /*<<< orphan*/  tree ;
struct ptr_info_def {scalar_t__ name_mem_tag; scalar_t__ value_escapes_p; int /*<<< orphan*/ * pt_vars; scalar_t__ is_dereferenced; } ;
struct TYPE_3__ {int /*<<< orphan*/  symbol_mem_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ RESULT_DECL ; 
 struct ptr_info_def* SSA_NAME_PTR_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VISITED (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_empty_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_variable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  internal_error (char*) ; 
 int /*<<< orphan*/  is_call_clobbered (scalar_t__) ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 
 size_t num_ssa_names ; 
 int /*<<< orphan*/  ssa_name (size_t) ; 
 TYPE_1__* var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_flow_sensitive_alias_info (void)
{
  size_t i;
  tree ptr;

  for (i = 1; i < num_ssa_names; i++)
    {
      tree var;
      var_ann_t ann;
      struct ptr_info_def *pi;
 

      ptr = ssa_name (i);
      if (!ptr)
	continue;

      /* We only care for pointers that are actually referenced in the
	 program.  */
      if (!POINTER_TYPE_P (TREE_TYPE (ptr)) || !TREE_VISITED (ptr))
	continue;

      /* RESULT_DECL is special.  If it's a GIMPLE register, then it
	 is only written-to only once in the return statement.
	 Otherwise, aggregate RESULT_DECLs may be written-to more than
	 once in virtual operands.  */
      var = SSA_NAME_VAR (ptr);
      if (TREE_CODE (var) == RESULT_DECL
	  && is_gimple_reg (ptr))
	continue;

      pi = SSA_NAME_PTR_INFO (ptr);
      if (pi == NULL)
	continue;

      ann = var_ann (var);
      if (pi->is_dereferenced && !pi->name_mem_tag && !ann->symbol_mem_tag)
	{
	  error ("dereferenced pointers should have a name or a symbol tag");
	  goto err;
	}

      if (pi->name_mem_tag
	  && (pi->pt_vars == NULL || bitmap_empty_p (pi->pt_vars)))
	{
	  error ("pointers with a memory tag, should have points-to sets");
	  goto err;
	}

      if (pi->value_escapes_p
	  && pi->name_mem_tag
	  && !is_call_clobbered (pi->name_mem_tag))
	{
	  error ("pointer escapes but its name tag is not call-clobbered");
	  goto err;
	}
    }

  return;

err:
  debug_variable (ptr);
  internal_error ("verify_flow_sensitive_alias_info failed");
}