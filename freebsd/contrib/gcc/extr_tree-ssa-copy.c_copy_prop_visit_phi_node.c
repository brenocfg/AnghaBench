#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {scalar_t__ member_1; scalar_t__ member_2; scalar_t__ value; scalar_t__ mem_ref; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ prop_value_t ;
typedef  enum ssa_prop_result { ____Placeholder_ssa_prop_result } ssa_prop_result ;
typedef  TYPE_2__* edge ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int EDGE_EXECUTABLE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_ARG_DEF (scalar_t__,int) ; 
 TYPE_2__* PHI_ARG_EDGE (scalar_t__,int) ; 
 int PHI_NUM_ARGS (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (scalar_t__) ; 
 int SSA_PROP_INTERESTING ; 
 int SSA_PROP_NOT_INTERESTING ; 
 int SSA_PROP_VARYING ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ do_store_copy_prop ; 
 int /*<<< orphan*/  dump_copy_of (scalar_t__,scalar_t__) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 TYPE_1__* get_copy_of_val (scalar_t__) ; 
 scalar_t__ get_last_copy_of (scalar_t__) ; 
 scalar_t__ loop_depth_of_name (scalar_t__) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int) ; 
 scalar_t__ set_copy_of_val (scalar_t__,scalar_t__,scalar_t__) ; 
 int simple_cst_equal (scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum ssa_prop_result
copy_prop_visit_phi_node (tree phi)
{
  enum ssa_prop_result retval;
  int i;
  tree lhs;
  prop_value_t phi_val = { 0, NULL_TREE, NULL_TREE };

  lhs = PHI_RESULT (phi);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nVisiting PHI node: ");
      print_generic_expr (dump_file, phi, dump_flags);
      fprintf (dump_file, "\n\n");
    }

  for (i = 0; i < PHI_NUM_ARGS (phi); i++)
    {
      prop_value_t *arg_val;
      tree arg = PHI_ARG_DEF (phi, i);
      edge e = PHI_ARG_EDGE (phi, i);

      /* We don't care about values flowing through non-executable
	 edges.  */
      if (!(e->flags & EDGE_EXECUTABLE))
	continue;

      /* Constants in the argument list never generate a useful copy.
	 Similarly, names that flow through abnormal edges cannot be
	 used to derive copies.  */
      if (TREE_CODE (arg) != SSA_NAME || SSA_NAME_OCCURS_IN_ABNORMAL_PHI (arg))
	{
	  phi_val.value = lhs;
	  break;
	}

      /* Avoid copy propagation from an inner into an outer loop.
	 Otherwise, this may move loop variant variables outside of
	 their loops and prevent coalescing opportunities.  If the
	 value was loop invariant, it will be hoisted by LICM and
	 exposed for copy propagation.  */
      if (loop_depth_of_name (arg) > loop_depth_of_name (lhs))
	{
	  phi_val.value = lhs;
	  break;
	}

      /* If the LHS appears in the argument list, ignore it.  It is
	 irrelevant as a copy.  */
      if (arg == lhs || get_last_copy_of (arg) == lhs)
	continue;

      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "\tArgument #%d: ", i);
	  dump_copy_of (dump_file, arg);
	  fprintf (dump_file, "\n");
	}

      arg_val = get_copy_of_val (arg);

      /* If the LHS didn't have a value yet, make it a copy of the
	 first argument we find.  Notice that while we make the LHS be
	 a copy of the argument itself, we take the memory reference
	 from the argument's value so that we can compare it to the
	 memory reference of all the other arguments.  */
      if (phi_val.value == NULL_TREE)
	{
	  phi_val.value = arg;
	  phi_val.mem_ref = arg_val->mem_ref;
	  continue;
	}

      /* If PHI_VAL and ARG don't have a common copy-of chain, then
	 this PHI node cannot be a copy operation.  Also, if we are
	 copy propagating stores and these two arguments came from
	 different memory references, they cannot be considered
	 copies.  */
      if (get_last_copy_of (phi_val.value) != get_last_copy_of (arg)
	  || (do_store_copy_prop
	      && phi_val.mem_ref
	      && arg_val->mem_ref
	      && simple_cst_equal (phi_val.mem_ref, arg_val->mem_ref) != 1))
	{
	  phi_val.value = lhs;
	  break;
	}
    }

  if (phi_val.value && set_copy_of_val (lhs, phi_val.value, phi_val.mem_ref))
    retval = (phi_val.value != lhs) ? SSA_PROP_INTERESTING : SSA_PROP_VARYING;
  else
    retval = SSA_PROP_NOT_INTERESTING;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nPHI node ");
      dump_copy_of (dump_file, lhs);
      fprintf (dump_file, "\nTelling the propagator to ");
      if (retval == SSA_PROP_INTERESTING)
	fprintf (dump_file, "add SSA edges out of this PHI and continue.");
      else if (retval == SSA_PROP_VARYING)
	fprintf (dump_file, "add SSA edges out of this PHI and never visit again.");
      else
	fprintf (dump_file, "do nothing with SSA edges and keep iterating.");
      fprintf (dump_file, "\n\n");
    }

  return retval;
}