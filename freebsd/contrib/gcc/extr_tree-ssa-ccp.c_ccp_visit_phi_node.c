#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct TYPE_13__ {int lattice_val; void* mem_ref; void* value; } ;
typedef  TYPE_3__ prop_value_t ;
typedef  enum ssa_prop_result { ____Placeholder_ssa_prop_result } ssa_prop_result ;
typedef  TYPE_4__* edge ;
struct TYPE_14__ {int flags; TYPE_2__* dest; TYPE_1__* src; } ;
struct TYPE_12__ {int index; } ;
struct TYPE_11__ {int index; } ;

/* Variables and functions */
#define  CONSTANT 132 
 int EDGE_EXECUTABLE ; 
 void* NULL_TREE ; 
 void* PHI_ARG_DEF (void*,int) ; 
 TYPE_4__* PHI_ARG_EDGE (void*,int) ; 
 int PHI_NUM_ARGS (void*) ; 
 void* PHI_RESULT (void*) ; 
 int SSA_PROP_INTERESTING ; 
 int SSA_PROP_NOT_INTERESTING ; 
 int SSA_PROP_VARYING ; 
 int TDF_DETAILS ; 
#define  UNDEFINED 131 
#define  UNINITIALIZED 130 
#define  UNKNOWN_VAL 129 
#define  VARYING 128 
 int /*<<< orphan*/  ccp_lattice_meet (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ do_store_ccp ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_lattice_value (scalar_t__,char*,TYPE_3__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_3__* get_value (void*,int) ; 
 scalar_t__ is_gimple_min_invariant (void*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,void*,int) ; 
 scalar_t__ set_lattice_value (void*,TYPE_3__) ; 

__attribute__((used)) static enum ssa_prop_result
ccp_visit_phi_node (tree phi)
{
  int i;
  prop_value_t *old_val, new_val;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nVisiting PHI node: ");
      print_generic_expr (dump_file, phi, dump_flags);
    }

  old_val = get_value (PHI_RESULT (phi), false);
  switch (old_val->lattice_val)
    {
    case VARYING:
      return SSA_PROP_VARYING;

    case CONSTANT:
      new_val = *old_val;
      break;

    case UNKNOWN_VAL:
      /* To avoid the default value of UNKNOWN_VAL overriding
         that of its possible constant arguments, temporarily
	 set the PHI node's default lattice value to be 
	 UNDEFINED.  If the PHI node's old value was UNKNOWN_VAL and
	 the new value is UNDEFINED, then we prevent the invalid
	 transition by not calling set_lattice_value.  */
      gcc_assert (do_store_ccp);

      /* FALLTHRU  */

    case UNDEFINED:
    case UNINITIALIZED:
      new_val.lattice_val = UNDEFINED;
      new_val.value = NULL_TREE;
      new_val.mem_ref = NULL_TREE;
      break;

    default:
      gcc_unreachable ();
    }

  for (i = 0; i < PHI_NUM_ARGS (phi); i++)
    {
      /* Compute the meet operator over all the PHI arguments flowing
	 through executable edges.  */
      edge e = PHI_ARG_EDGE (phi, i);

      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file,
	      "\n    Argument #%d (%d -> %d %sexecutable)\n",
	      i, e->src->index, e->dest->index,
	      (e->flags & EDGE_EXECUTABLE) ? "" : "not ");
	}

      /* If the incoming edge is executable, Compute the meet operator for
	 the existing value of the PHI node and the current PHI argument.  */
      if (e->flags & EDGE_EXECUTABLE)
	{
	  tree arg = PHI_ARG_DEF (phi, i);
	  prop_value_t arg_val;

	  if (is_gimple_min_invariant (arg))
	    {
	      arg_val.lattice_val = CONSTANT;
	      arg_val.value = arg;
	      arg_val.mem_ref = NULL_TREE;
	    }
	  else
	    arg_val = *(get_value (arg, true));

	  ccp_lattice_meet (&new_val, &arg_val);

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "\t");
	      print_generic_expr (dump_file, arg, dump_flags);
	      dump_lattice_value (dump_file, "\tValue: ", arg_val);
	      fprintf (dump_file, "\n");
	    }

	  if (new_val.lattice_val == VARYING)
	    break;
	}
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      dump_lattice_value (dump_file, "\n    PHI node value: ", new_val);
      fprintf (dump_file, "\n\n");
    }

  /* Check for an invalid change from UNKNOWN_VAL to UNDEFINED.  */
  if (do_store_ccp
      && old_val->lattice_val == UNKNOWN_VAL
      && new_val.lattice_val == UNDEFINED)
    return SSA_PROP_NOT_INTERESTING;

  /* Otherwise, make the transition to the new value.  */
  if (set_lattice_value (PHI_RESULT (phi), new_val))
    {
      if (new_val.lattice_val == VARYING)
	return SSA_PROP_VARYING;
      else
	return SSA_PROP_INTERESTING;
    }
  else
    return SSA_PROP_NOT_INTERESTING;
}