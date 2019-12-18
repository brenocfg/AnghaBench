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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ save_expr (scalar_t__) ; 
 scalar_t__ ssize_int (int /*<<< orphan*/ ) ; 
 scalar_t__ vtable_entry_type ; 

__attribute__((used)) static tree
thunk_adjust (tree ptr, bool this_adjusting,
	      HOST_WIDE_INT fixed_offset, tree virtual_offset)
{
  if (this_adjusting)
    /* Adjust the pointer by the constant.  */
    ptr = fold_build2 (PLUS_EXPR, TREE_TYPE (ptr), ptr,
		       ssize_int (fixed_offset));

  /* If there's a virtual offset, look up that value in the vtable and
     adjust the pointer again.  */
  if (virtual_offset)
    {
      tree vtable;

      ptr = save_expr (ptr);
      /* The vptr is always at offset zero in the object.  */
      vtable = build1 (NOP_EXPR,
		       build_pointer_type (build_pointer_type
					   (vtable_entry_type)),
		       ptr);
      /* Form the vtable address.  */
      vtable = build1 (INDIRECT_REF, TREE_TYPE (TREE_TYPE (vtable)), vtable);
      /* Find the entry with the vcall offset.  */
      vtable = build2 (PLUS_EXPR, TREE_TYPE (vtable), vtable, virtual_offset);
      /* Get the offset itself.  */
      vtable = build1 (INDIRECT_REF, TREE_TYPE (TREE_TYPE (vtable)), vtable);
      /* Adjust the `this' pointer.  */
      ptr = fold_build2 (PLUS_EXPR, TREE_TYPE (ptr), ptr, vtable);
    }

  if (!this_adjusting)
    /* Adjust the pointer by the constant.  */
    ptr = fold_build2 (PLUS_EXPR, TREE_TYPE (ptr), ptr,
		       ssize_int (fixed_offset));

  return ptr;
}