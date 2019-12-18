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
#define  COMPONENT_REF 132 
#define  COMPOUND_EXPR 131 
#define  COND_EXPR 130 
 int /*<<< orphan*/  DECL_BIT_FIELD_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_C_BIT_FIELD (int /*<<< orphan*/ ) ; 
 int FIELD_DECL ; 
#define  MODIFY_EXPR 129 
 int /*<<< orphan*/  NULL_TREE ; 
#define  SAVE_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
is_bitfield_expr_with_lowered_type (tree exp)
{
  switch (TREE_CODE (exp))
    {
    case COND_EXPR:
      if (!is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 1)))
	return NULL_TREE;
      return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 2));

    case COMPOUND_EXPR:
      return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 1));

    case MODIFY_EXPR:
    case SAVE_EXPR:
      return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 0));

    case COMPONENT_REF:
      {
	tree field;
	
	field = TREE_OPERAND (exp, 1);
	if (TREE_CODE (field) != FIELD_DECL || !DECL_C_BIT_FIELD (field))
	  return NULL_TREE;
	if (same_type_ignoring_top_level_qualifiers_p
	    (TREE_TYPE (exp), DECL_BIT_FIELD_TYPE (field)))
	  return NULL_TREE;
	return DECL_BIT_FIELD_TYPE (field);
      }

    default:
      return NULL_TREE;
    }
}