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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  OBJ_TYPE_REF ; 
 scalar_t__ TARGET_VTABLE_USES_DESCRIPTORS ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_vtbl_ref_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
build_vfn_ref (tree instance_ptr, tree idx)
{
  tree aref;

  aref = build_vtbl_ref_1 (build_indirect_ref (instance_ptr, 0), idx);

  /* When using function descriptors, the address of the
     vtable entry is treated as a function pointer.  */
  if (TARGET_VTABLE_USES_DESCRIPTORS)
    aref = build1 (NOP_EXPR, TREE_TYPE (aref),
		   build_unary_op (ADDR_EXPR, aref, /*noconvert=*/1));

  /* Remember this as a method reference, for later devirtualization.  */
  aref = build3 (OBJ_TYPE_REF, TREE_TYPE (aref), aref, instance_ptr, idx);

  return aref;
}