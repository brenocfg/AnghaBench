#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* type_for_size ) (scalar_t__,int) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ BIT_AND_EXPR ; 
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ PLACEHOLDER_EXPR ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 int TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 scalar_t__ const_binop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_build2 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ force_fit_type (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ get_inner_reference (scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,int*,int*,int*,int) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  size_int (scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,int) ; 

__attribute__((used)) static tree
decode_field_reference (tree exp, HOST_WIDE_INT *pbitsize,
			HOST_WIDE_INT *pbitpos, enum machine_mode *pmode,
			int *punsignedp, int *pvolatilep,
			tree *pmask, tree *pand_mask)
{
  tree outer_type = 0;
  tree and_mask = 0;
  tree mask, inner, offset;
  tree unsigned_type;
  unsigned int precision;

  /* All the optimizations using this function assume integer fields.
     There are problems with FP fields since the type_for_size call
     below can fail for, e.g., XFmode.  */
  if (! INTEGRAL_TYPE_P (TREE_TYPE (exp)))
    return 0;

  /* We are interested in the bare arrangement of bits, so strip everything
     that doesn't affect the machine mode.  However, record the type of the
     outermost expression if it may matter below.  */
  if (TREE_CODE (exp) == NOP_EXPR
      || TREE_CODE (exp) == CONVERT_EXPR
      || TREE_CODE (exp) == NON_LVALUE_EXPR)
    outer_type = TREE_TYPE (exp);
  STRIP_NOPS (exp);

  if (TREE_CODE (exp) == BIT_AND_EXPR)
    {
      and_mask = TREE_OPERAND (exp, 1);
      exp = TREE_OPERAND (exp, 0);
      STRIP_NOPS (exp); STRIP_NOPS (and_mask);
      if (TREE_CODE (and_mask) != INTEGER_CST)
	return 0;
    }

  inner = get_inner_reference (exp, pbitsize, pbitpos, &offset, pmode,
			       punsignedp, pvolatilep, false);
  if ((inner == exp && and_mask == 0)
      || *pbitsize < 0 || offset != 0
      || TREE_CODE (inner) == PLACEHOLDER_EXPR)
    return 0;

  /* If the number of bits in the reference is the same as the bitsize of
     the outer type, then the outer type gives the signedness. Otherwise
     (in case of a small bitfield) the signedness is unchanged.  */
  if (outer_type && *pbitsize == TYPE_PRECISION (outer_type))
    *punsignedp = TYPE_UNSIGNED (outer_type);

  /* Compute the mask to access the bitfield.  */
  unsigned_type = lang_hooks.types.type_for_size (*pbitsize, 1);
  precision = TYPE_PRECISION (unsigned_type);

  mask = build_int_cst (unsigned_type, -1);
  mask = force_fit_type (mask, 0, false, false);

  mask = const_binop (LSHIFT_EXPR, mask, size_int (precision - *pbitsize), 0);
  mask = const_binop (RSHIFT_EXPR, mask, size_int (precision - *pbitsize), 0);

  /* Merge it with the mask we found in the BIT_AND_EXPR, if any.  */
  if (and_mask != 0)
    mask = fold_build2 (BIT_AND_EXPR, unsigned_type,
			fold_convert (unsigned_type, and_mask), mask);

  *pmask = mask;
  *pand_mask = and_mask;
  return inner;
}