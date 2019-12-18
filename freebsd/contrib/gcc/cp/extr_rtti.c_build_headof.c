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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ POINTER_TYPE ; 
 int TARGET_VTABLE_DATA_ENTRY_DISTANCE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_POLYMORPHIC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_qualified_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_vtbl_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_type_quals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  ptrdiff_type_node ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
build_headof (tree exp)
{
  tree type = TREE_TYPE (exp);
  tree offset;
  tree index;

  gcc_assert (TREE_CODE (type) == POINTER_TYPE);
  type = TREE_TYPE (type);

  if (!TYPE_POLYMORPHIC_P (type))
    return exp;

  /* We use this a couple of times below, protect it.  */
  exp = save_expr (exp);

  /* The offset-to-top field is at index -2 from the vptr.  */
  index = build_int_cst (NULL_TREE,
			 -2 * TARGET_VTABLE_DATA_ENTRY_DISTANCE);

  offset = build_vtbl_ref (build_indirect_ref (exp, NULL), index);

  type = build_qualified_type (ptr_type_node,
			       cp_type_quals (TREE_TYPE (exp)));
  return build2 (PLUS_EXPR, type, exp,
		 convert_to_integer (ptrdiff_type_node, offset));
}