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
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ SUBSTITUTE_PLACEHOLDER_IN_EXPR (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ALIGN_UNIT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (int /*<<< orphan*/ ) ; 
 scalar_t__ sizetype ; 

tree
array_ref_element_size (tree exp)
{
  tree aligned_size = TREE_OPERAND (exp, 3);
  tree elmt_type = TREE_TYPE (TREE_TYPE (TREE_OPERAND (exp, 0)));

  /* If a size was specified in the ARRAY_REF, it's the size measured
     in alignment units of the element type.  So multiply by that value.  */
  if (aligned_size)
    {
      /* ??? tree_ssa_useless_type_conversion will eliminate casts to
	 sizetype from another type of the same width and signedness.  */
      if (TREE_TYPE (aligned_size) != sizetype)
	aligned_size = fold_convert (sizetype, aligned_size);
      return size_binop (MULT_EXPR, aligned_size,
		         size_int (TYPE_ALIGN_UNIT (elmt_type)));
    }

  /* Otherwise, take the size from that of the element type.  Substitute
     any PLACEHOLDER_EXPR that we have.  */
  else
    return SUBSTITUTE_PLACEHOLDER_IN_EXPR (TYPE_SIZE_UNIT (elmt_type), exp);
}