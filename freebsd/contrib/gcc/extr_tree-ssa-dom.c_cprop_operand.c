#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  scalar_t__ tree ;
struct TYPE_4__ {int /*<<< orphan*/  (* types_compatible_p ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  num_copy_prop; int /*<<< orphan*/  num_const_prop; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ ASM_EXPR ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_VALUE (scalar_t__) ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ USE_FROM_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ VALUE_HANDLE ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 scalar_t__ get_virtual_var (scalar_t__) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ is_gimple_reg (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ loop_depth_of_name (scalar_t__) ; 
 int /*<<< orphan*/  mark_stmt_modified (scalar_t__) ; 
 int /*<<< orphan*/  may_propagate_copy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  may_propagate_copy_into_asm (scalar_t__) ; 
 TYPE_1__ opt_stats ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  propagate_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
cprop_operand (tree stmt, use_operand_p op_p)
{
  bool may_have_exposed_new_symbols = false;
  tree val;
  tree op = USE_FROM_PTR (op_p);

  /* If the operand has a known constant value or it is known to be a
     copy of some other variable, use the value or copy stored in
     CONST_AND_COPIES.  */
  val = SSA_NAME_VALUE (op);
  if (val && val != op && TREE_CODE (val) != VALUE_HANDLE)
    {
      tree op_type, val_type;

      /* Do not change the base variable in the virtual operand
	 tables.  That would make it impossible to reconstruct
	 the renamed virtual operand if we later modify this
	 statement.  Also only allow the new value to be an SSA_NAME
	 for propagation into virtual operands.  */
      if (!is_gimple_reg (op)
	  && (TREE_CODE (val) != SSA_NAME
	      || is_gimple_reg (val)
	      || get_virtual_var (val) != get_virtual_var (op)))
	return false;

      /* Do not replace hard register operands in asm statements.  */
      if (TREE_CODE (stmt) == ASM_EXPR
	  && !may_propagate_copy_into_asm (op))
	return false;

      /* Get the toplevel type of each operand.  */
      op_type = TREE_TYPE (op);
      val_type = TREE_TYPE (val);

      /* While both types are pointers, get the type of the object
	 pointed to.  */
      while (POINTER_TYPE_P (op_type) && POINTER_TYPE_P (val_type))
	{
	  op_type = TREE_TYPE (op_type);
	  val_type = TREE_TYPE (val_type);
	}

      /* Make sure underlying types match before propagating a constant by
	 converting the constant to the proper type.  Note that convert may
	 return a non-gimple expression, in which case we ignore this
	 propagation opportunity.  */
      if (TREE_CODE (val) != SSA_NAME)
	{
	  if (!lang_hooks.types_compatible_p (op_type, val_type))
	    {
	      val = fold_convert (TREE_TYPE (op), val);
	      if (!is_gimple_min_invariant (val))
		return false;
	    }
	}

      /* Certain operands are not allowed to be copy propagated due
	 to their interaction with exception handling and some GCC
	 extensions.  */
      else if (!may_propagate_copy (op, val))
	return false;
      
      /* Do not propagate copies if the propagated value is at a deeper loop
	 depth than the propagatee.  Otherwise, this may move loop variant
	 variables outside of their loops and prevent coalescing
	 opportunities.  If the value was loop invariant, it will be hoisted
	 by LICM and exposed for copy propagation.  */
      if (loop_depth_of_name (val) > loop_depth_of_name (op))
	return false;

      /* Dump details.  */
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "  Replaced '");
	  print_generic_expr (dump_file, op, dump_flags);
	  fprintf (dump_file, "' with %s '",
		   (TREE_CODE (val) != SSA_NAME ? "constant" : "variable"));
	  print_generic_expr (dump_file, val, dump_flags);
	  fprintf (dump_file, "'\n");
	}

      /* If VAL is an ADDR_EXPR or a constant of pointer type, note
	 that we may have exposed a new symbol for SSA renaming.  */
      if (TREE_CODE (val) == ADDR_EXPR
	  || (POINTER_TYPE_P (TREE_TYPE (op))
	      && is_gimple_min_invariant (val)))
	may_have_exposed_new_symbols = true;

      if (TREE_CODE (val) != SSA_NAME)
	opt_stats.num_const_prop++;
      else
	opt_stats.num_copy_prop++;

      propagate_value (op_p, val);

      /* And note that we modified this statement.  This is now
	 safe, even if we changed virtual operands since we will
	 rescan the statement and rewrite its operands again.  */
      mark_stmt_modified (stmt);
    }
  return may_have_exposed_new_symbols;
}