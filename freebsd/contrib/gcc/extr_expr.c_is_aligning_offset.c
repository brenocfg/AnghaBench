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
 scalar_t__ ADDR_EXPR ; 
 int BIGGEST_ALIGNMENT ; 
 int BITS_PER_UNIT ; 
 scalar_t__ BIT_AND_EXPR ; 
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ NEGATE_EXPR ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ compare_tree_int (scalar_t__,int) ; 
 int /*<<< orphan*/  exact_log2 (scalar_t__) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 scalar_t__ tree_low_cst (scalar_t__,int) ; 

__attribute__((used)) static int
is_aligning_offset (tree offset, tree exp)
{
  /* Strip off any conversions.  */
  while (TREE_CODE (offset) == NON_LVALUE_EXPR
	 || TREE_CODE (offset) == NOP_EXPR
	 || TREE_CODE (offset) == CONVERT_EXPR)
    offset = TREE_OPERAND (offset, 0);

  /* We must now have a BIT_AND_EXPR with a constant that is one less than
     power of 2 and which is larger than BIGGEST_ALIGNMENT.  */
  if (TREE_CODE (offset) != BIT_AND_EXPR
      || !host_integerp (TREE_OPERAND (offset, 1), 1)
      || compare_tree_int (TREE_OPERAND (offset, 1),
			   BIGGEST_ALIGNMENT / BITS_PER_UNIT) <= 0
      || !exact_log2 (tree_low_cst (TREE_OPERAND (offset, 1), 1) + 1) < 0)
    return 0;

  /* Look at the first operand of BIT_AND_EXPR and strip any conversion.
     It must be NEGATE_EXPR.  Then strip any more conversions.  */
  offset = TREE_OPERAND (offset, 0);
  while (TREE_CODE (offset) == NON_LVALUE_EXPR
	 || TREE_CODE (offset) == NOP_EXPR
	 || TREE_CODE (offset) == CONVERT_EXPR)
    offset = TREE_OPERAND (offset, 0);

  if (TREE_CODE (offset) != NEGATE_EXPR)
    return 0;

  offset = TREE_OPERAND (offset, 0);
  while (TREE_CODE (offset) == NON_LVALUE_EXPR
	 || TREE_CODE (offset) == NOP_EXPR
	 || TREE_CODE (offset) == CONVERT_EXPR)
    offset = TREE_OPERAND (offset, 0);

  /* This must now be the address of EXP.  */
  return TREE_CODE (offset) == ADDR_EXPR && TREE_OPERAND (offset, 0) == exp;
}