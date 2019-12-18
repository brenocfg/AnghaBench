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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int vtable_method; } ;
struct TYPE_4__ {TYPE_1__ local; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  BINFO_VIRTUALS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BV_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_VINDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_TYPE_REF_TOKEN (int /*<<< orphan*/ ) ; 
 int TARGET_VTABLE_USES_DESCRIPTORS ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_address (int /*<<< orphan*/ ) ; 
 TYPE_2__* cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_low_cst (int /*<<< orphan*/ ,int) ; 

tree
cp_fold_obj_type_ref (tree ref, tree known_type)
{
  HOST_WIDE_INT index = tree_low_cst (OBJ_TYPE_REF_TOKEN (ref), 1);
  HOST_WIDE_INT i = 0;
  tree v = BINFO_VIRTUALS (TYPE_BINFO (known_type));
  tree fndecl;

  while (i != index)
    {
      i += (TARGET_VTABLE_USES_DESCRIPTORS
	    ? TARGET_VTABLE_USES_DESCRIPTORS : 1);
      v = TREE_CHAIN (v);
    }

  fndecl = BV_FN (v);

#ifdef ENABLE_CHECKING
  gcc_assert (tree_int_cst_equal (OBJ_TYPE_REF_TOKEN (ref),
				  DECL_VINDEX (fndecl)));
#endif

  cgraph_node (fndecl)->local.vtable_method = true;

  return build_address (fndecl);
}