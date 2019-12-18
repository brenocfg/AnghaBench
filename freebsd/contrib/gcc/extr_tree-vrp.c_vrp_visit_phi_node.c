#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ type; void* min; void* max; int /*<<< orphan*/ * equiv; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ value_range_t ;
typedef  void* tree ;
typedef  enum ssa_prop_result { ____Placeholder_ssa_prop_result } ssa_prop_result ;
typedef  TYPE_4__* edge ;
struct TYPE_17__ {int flags; TYPE_2__* dest; TYPE_1__* src; } ;
struct TYPE_15__ {int index; } ;
struct TYPE_14__ {int index; } ;
typedef  int /*<<< orphan*/  TREE_OVERFLOW ;

/* Variables and functions */
 int EDGE_EXECUTABLE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 void* PHI_ARG_DEF (void*,int) ; 
 TYPE_4__* PHI_ARG_EDGE (void*,int) ; 
 int PHI_NUM_ARGS (void*) ; 
 void* PHI_RESULT (void*) ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int SSA_PROP_INTERESTING ; 
 int SSA_PROP_NOT_INTERESTING ; 
 int SSA_PROP_VARYING ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (void*) ; 
 int /*<<< orphan*/  TREE_TYPE (void*) ; 
 void* TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 void* TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ VR_RANGE ; 
 int /*<<< orphan*/  VR_UNDEFINED ; 
 scalar_t__ VR_VARYING ; 
 int compare_values (void*,void*) ; 
 void* copy_node (void*) ; 
 int /*<<< orphan*/  copy_value_range (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_value_range (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 TYPE_3__* get_value_range (void*) ; 
 scalar_t__ is_overflow_infinity (void*) ; 
 int /*<<< orphan*/  needs_overflow_infinity (int /*<<< orphan*/ ) ; 
 void* negative_overflow_infinity (int /*<<< orphan*/ ) ; 
 void* positive_overflow_infinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  set_value_range_to_varying (TYPE_3__*) ; 
 scalar_t__ supports_overflow_infinity (int /*<<< orphan*/ ) ; 
 scalar_t__ update_value_range (void*,TYPE_3__*) ; 
 int /*<<< orphan*/  vrp_meet (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ vrp_val_is_max (void*) ; 
 scalar_t__ vrp_val_is_min (void*) ; 
 int /*<<< orphan*/  vrp_var_may_overflow (void*,void*) ; 

__attribute__((used)) static enum ssa_prop_result
vrp_visit_phi_node (tree phi)
{
  int i;
  tree lhs = PHI_RESULT (phi);
  value_range_t *lhs_vr = get_value_range (lhs);
  value_range_t vr_result = { VR_UNDEFINED, NULL_TREE, NULL_TREE, NULL };

  copy_value_range (&vr_result, lhs_vr);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nVisiting PHI node: ");
      print_generic_expr (dump_file, phi, dump_flags);
    }

  for (i = 0; i < PHI_NUM_ARGS (phi); i++)
    {
      edge e = PHI_ARG_EDGE (phi, i);

      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file,
	      "\n    Argument #%d (%d -> %d %sexecutable)\n",
	      i, e->src->index, e->dest->index,
	      (e->flags & EDGE_EXECUTABLE) ? "" : "not ");
	}

      if (e->flags & EDGE_EXECUTABLE)
	{
	  tree arg = PHI_ARG_DEF (phi, i);
	  value_range_t vr_arg;

	  if (TREE_CODE (arg) == SSA_NAME)
	    vr_arg = *(get_value_range (arg));
	  else
	    {
	      if (is_overflow_infinity (arg))
		{
		  arg = copy_node (arg);
		  TREE_OVERFLOW (arg) = 0;
		}

	      vr_arg.type = VR_RANGE;
	      vr_arg.min = arg;
	      vr_arg.max = arg;
	      vr_arg.equiv = NULL;
	    }

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "\t");
	      print_generic_expr (dump_file, arg, dump_flags);
	      fprintf (dump_file, "\n\tValue: ");
	      dump_value_range (dump_file, &vr_arg);
	      fprintf (dump_file, "\n");
	    }

	  vrp_meet (&vr_result, &vr_arg);

	  if (vr_result.type == VR_VARYING)
	    break;
	}
    }

  if (vr_result.type == VR_VARYING)
    goto varying;

  /* To prevent infinite iterations in the algorithm, derive ranges
     when the new value is slightly bigger or smaller than the
     previous one.  */
  if (lhs_vr->type == VR_RANGE && vr_result.type == VR_RANGE)
    {
      if (!POINTER_TYPE_P (TREE_TYPE (lhs)))
	{
	  int cmp_min = compare_values (lhs_vr->min, vr_result.min);
	  int cmp_max = compare_values (lhs_vr->max, vr_result.max);

	  /* If the new minimum is smaller or larger than the previous
	     one, go all the way to -INF.  In the first case, to avoid
	     iterating millions of times to reach -INF, and in the
	     other case to avoid infinite bouncing between different
	     minimums.  */
	  if (cmp_min > 0 || cmp_min < 0)
	    {
	      /* If we will end up with a (-INF, +INF) range, set it
		 to VARYING.  */
	      if (vrp_val_is_max (vr_result.max))
		goto varying;

	      if (!needs_overflow_infinity (TREE_TYPE (vr_result.min))
		  || !vrp_var_may_overflow (lhs, phi))
		vr_result.min = TYPE_MIN_VALUE (TREE_TYPE (vr_result.min));
	      else if (supports_overflow_infinity (TREE_TYPE (vr_result.min)))
		vr_result.min =
		  negative_overflow_infinity (TREE_TYPE (vr_result.min));
	      else
		goto varying;
	    }

	  /* Similarly, if the new maximum is smaller or larger than
	     the previous one, go all the way to +INF.  */
	  if (cmp_max < 0 || cmp_max > 0)
	    {
	      /* If we will end up with a (-INF, +INF) range, set it
		 to VARYING.  */
	      if (vrp_val_is_min (vr_result.min))
		goto varying;

	      if (!needs_overflow_infinity (TREE_TYPE (vr_result.max))
		  || !vrp_var_may_overflow (lhs, phi))
		vr_result.max = TYPE_MAX_VALUE (TREE_TYPE (vr_result.max));
	      else if (supports_overflow_infinity (TREE_TYPE (vr_result.max)))
		vr_result.max =
		  positive_overflow_infinity (TREE_TYPE (vr_result.max));
	      else
		goto varying;
	    }
	}
    }

  /* If the new range is different than the previous value, keep
     iterating.  */
  if (update_value_range (lhs, &vr_result))
    return SSA_PROP_INTERESTING;

  /* Nothing changed, don't add outgoing edges.  */
  return SSA_PROP_NOT_INTERESTING;

  /* No match found.  Set the LHS to VARYING.  */
varying:
  set_value_range_to_varying (lhs_vr);
  return SSA_PROP_VARYING;
}