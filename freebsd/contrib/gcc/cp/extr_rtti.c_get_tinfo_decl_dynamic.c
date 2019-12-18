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
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TARGET_VTABLE_DATA_ENTRY_DISTANCE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_POLYMORPHIC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_vtbl_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type_or_else (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 scalar_t__ error_operand_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tinfo_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  non_reference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolves_to_fixed_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_info_ptr_type ; 

__attribute__((used)) static tree
get_tinfo_decl_dynamic (tree exp)
{
  tree type;
  tree t;

  if (error_operand_p (exp))
    return error_mark_node;

  /* peel back references, so they match.  */
  type = non_reference (TREE_TYPE (exp));

  /* Peel off cv qualifiers.  */
  type = TYPE_MAIN_VARIANT (type);

  if (CLASS_TYPE_P (type))
    type = complete_type_or_else (type, exp);

  if (!type)
    return error_mark_node;

  /* If exp is a reference to polymorphic type, get the real type_info.  */
  if (TYPE_POLYMORPHIC_P (type) && ! resolves_to_fixed_type_p (exp, 0))
    {
      /* build reference to type_info from vtable.  */
      tree index;

      /* The RTTI information is at index -1.  */
      index = build_int_cst (NULL_TREE,
			     -1 * TARGET_VTABLE_DATA_ENTRY_DISTANCE);
      t = build_vtbl_ref (exp, index);
      t = convert (type_info_ptr_type, t);
    }
  else
    /* Otherwise return the type_info for the static type of the expr.  */
    t = get_tinfo_ptr (TYPE_MAIN_VARIANT (type));

  return build_indirect_ref (t, NULL);
}