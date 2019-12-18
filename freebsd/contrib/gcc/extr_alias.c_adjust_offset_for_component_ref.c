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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ DECL_FIELD_BIT_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ component_ref_field_offset (scalar_t__) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 int tree_low_cst (scalar_t__,int) ; 

__attribute__((used)) static rtx
adjust_offset_for_component_ref (tree x, rtx offset)
{
  HOST_WIDE_INT ioffset;

  if (! offset)
    return NULL_RTX;

  ioffset = INTVAL (offset);
  do
    {
      tree offset = component_ref_field_offset (x);
      tree field = TREE_OPERAND (x, 1);

      if (! host_integerp (offset, 1))
	return NULL_RTX;
      ioffset += (tree_low_cst (offset, 1)
		  + (tree_low_cst (DECL_FIELD_BIT_OFFSET (field), 1)
		     / BITS_PER_UNIT));

      x = TREE_OPERAND (x, 0);
    }
  while (x && TREE_CODE (x) == COMPONENT_REF);

  return GEN_INT (ioffset);
}