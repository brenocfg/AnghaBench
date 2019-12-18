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

/* Variables and functions */
 scalar_t__ BINFO_VPTR_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_indirect_ref (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_modify_expr (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_vfield_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_vtbl_address (scalar_t__) ; 
 scalar_t__ convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ convert_force (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ current_in_charge_parm ; 
 scalar_t__ current_vtt_parm ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_expr_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ integer_zero_node ; 

__attribute__((used)) static void
expand_virtual_init (tree binfo, tree decl)
{
  tree vtbl, vtbl_ptr;
  tree vtt_index;

  /* Compute the initializer for vptr.  */
  vtbl = build_vtbl_address (binfo);

  /* We may get this vptr from a VTT, if this is a subobject
     constructor or subobject destructor.  */
  vtt_index = BINFO_VPTR_INDEX (binfo);
  if (vtt_index)
    {
      tree vtbl2;
      tree vtt_parm;

      /* Compute the value to use, when there's a VTT.  */
      vtt_parm = current_vtt_parm;
      vtbl2 = build2 (PLUS_EXPR,
		      TREE_TYPE (vtt_parm),
		      vtt_parm,
		      vtt_index);
      vtbl2 = build_indirect_ref (vtbl2, NULL);
      vtbl2 = convert (TREE_TYPE (vtbl), vtbl2);

      /* The actual initializer is the VTT value only in the subobject
	 constructor.  In maybe_clone_body we'll substitute NULL for
	 the vtt_parm in the case of the non-subobject constructor.  */
      vtbl = build3 (COND_EXPR,
		     TREE_TYPE (vtbl),
		     build2 (EQ_EXPR, boolean_type_node,
			     current_in_charge_parm, integer_zero_node),
		     vtbl2,
		     vtbl);
    }

  /* Compute the location of the vtpr.  */
  vtbl_ptr = build_vfield_ref (build_indirect_ref (decl, NULL),
			       TREE_TYPE (binfo));
  gcc_assert (vtbl_ptr != error_mark_node);

  /* Assign the vtable to the vptr.  */
  vtbl = convert_force (TREE_TYPE (vtbl_ptr), vtbl, 0);
  finish_expr_stmt (build_modify_expr (vtbl_ptr, NOP_EXPR, vtbl));
}