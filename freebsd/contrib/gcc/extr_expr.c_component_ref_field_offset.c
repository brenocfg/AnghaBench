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
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  DECL_FIELD_OFFSET (scalar_t__) ; 
 int DECL_OFFSET_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ SUBSTITUTE_PLACEHOLDER_IN_EXPR (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (int) ; 
 scalar_t__ sizetype ; 

tree
component_ref_field_offset (tree exp)
{
  tree aligned_offset = TREE_OPERAND (exp, 2);
  tree field = TREE_OPERAND (exp, 1);

  /* If an offset was specified in the COMPONENT_REF, it's the offset measured
     in units of DECL_OFFSET_ALIGN / BITS_PER_UNIT.  So multiply by that
     value.  */
  if (aligned_offset)
    {
      /* ??? tree_ssa_useless_type_conversion will eliminate casts to
	 sizetype from another type of the same width and signedness.  */
      if (TREE_TYPE (aligned_offset) != sizetype)
	aligned_offset = fold_convert (sizetype, aligned_offset);
      return size_binop (MULT_EXPR, aligned_offset,
		         size_int (DECL_OFFSET_ALIGN (field) / BITS_PER_UNIT));
    }

  /* Otherwise, take the offset from that of the field.  Substitute
     any PLACEHOLDER_EXPR that we have.  */
  else
    return SUBSTITUTE_PLACEHOLDER_IN_EXPR (DECL_FIELD_OFFSET (field), exp);
}