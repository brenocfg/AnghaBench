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
 int /*<<< orphan*/  COND_EXPR ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPEID_EXPR ; 
 scalar_t__ TYPE_POLYMORPHIC_P (scalar_t__) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  const_type_info_type_node ; 
 scalar_t__ cp_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ get_tinfo_decl_dynamic (scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  resolves_to_fixed_type_p (scalar_t__,int*) ; 
 scalar_t__ stabilize_reference (scalar_t__) ; 
 scalar_t__ throw_bad_typeid () ; 
 int /*<<< orphan*/  typeid_ok_p () ; 

tree
build_typeid (tree exp)
{
  tree cond = NULL_TREE;
  int nonnull = 0;

  if (exp == error_mark_node || !typeid_ok_p ())
    return error_mark_node;

  if (processing_template_decl)
    return build_min (TYPEID_EXPR, const_type_info_type_node, exp);

  if (TREE_CODE (exp) == INDIRECT_REF
      && TREE_CODE (TREE_TYPE (TREE_OPERAND (exp, 0))) == POINTER_TYPE
      && TYPE_POLYMORPHIC_P (TREE_TYPE (exp))
      && ! resolves_to_fixed_type_p (exp, &nonnull)
      && ! nonnull)
    {
      exp = stabilize_reference (exp);
      cond = cp_convert (boolean_type_node, TREE_OPERAND (exp, 0));
    }

  exp = get_tinfo_decl_dynamic (exp);

  if (exp == error_mark_node)
    return error_mark_node;

  if (cond)
    {
      tree bad = throw_bad_typeid ();

      exp = build3 (COND_EXPR, TREE_TYPE (exp), cond, exp, bad);
    }

  return exp;
}