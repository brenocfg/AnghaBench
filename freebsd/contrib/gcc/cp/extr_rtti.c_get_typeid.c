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
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TYPEID_EXPR ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ build_indirect_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ build_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ complete_type_or_else (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_type_info_type_node ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  get_tinfo_ptr (scalar_t__) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  typeid_ok_p () ; 

tree
get_typeid (tree type)
{
  if (type == error_mark_node || !typeid_ok_p ())
    return error_mark_node;

  if (processing_template_decl)
    return build_min (TYPEID_EXPR, const_type_info_type_node, type);

  /* If the type of the type-id is a reference type, the result of the
     typeid expression refers to a type_info object representing the
     referenced type.  */
  type = non_reference (type);

  /* The top-level cv-qualifiers of the lvalue expression or the type-id
     that is the operand of typeid are always ignored.  */
  type = TYPE_MAIN_VARIANT (type);

  if (CLASS_TYPE_P (type))
    type = complete_type_or_else (type, NULL_TREE);

  if (!type)
    return error_mark_node;

  return build_indirect_ref (get_tinfo_ptr (type), NULL);
}