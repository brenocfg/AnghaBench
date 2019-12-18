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
struct TYPE_3__ {scalar_t__ (* signed_type ) (scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 int /*<<< orphan*/  BIT_XOR_EXPR ; 
 int GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ const_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ size_int (int) ; 
 scalar_t__ stub1 (scalar_t__) ; 

__attribute__((used)) static tree
unextend (tree c, int p, int unsignedp, tree mask)
{
  tree type = TREE_TYPE (c);
  int modesize = GET_MODE_BITSIZE (TYPE_MODE (type));
  tree temp;

  if (p == modesize || unsignedp)
    return c;

  /* We work by getting just the sign bit into the low-order bit, then
     into the high-order bit, then sign-extend.  We then XOR that value
     with C.  */
  temp = const_binop (RSHIFT_EXPR, c, size_int (p - 1), 0);
  temp = const_binop (BIT_AND_EXPR, temp, size_int (1), 0);

  /* We must use a signed type in order to get an arithmetic right shift.
     However, we must also avoid introducing accidental overflows, so that
     a subsequent call to integer_zerop will work.  Hence we must
     do the type conversion here.  At this point, the constant is either
     zero or one, and the conversion to a signed type can never overflow.
     We could get an overflow if this conversion is done anywhere else.  */
  if (TYPE_UNSIGNED (type))
    temp = fold_convert (lang_hooks.types.signed_type (type), temp);

  temp = const_binop (LSHIFT_EXPR, temp, size_int (modesize - 1), 0);
  temp = const_binop (RSHIFT_EXPR, temp, size_int (modesize - p - 1), 0);
  if (mask != 0)
    temp = const_binop (BIT_AND_EXPR, temp,
			fold_convert (TREE_TYPE (c), mask), 0);
  /* If necessary, convert the type back to match the type of C.  */
  if (TYPE_UNSIGNED (type))
    temp = fold_convert (type, temp);

  return fold_convert (type, const_binop (BIT_XOR_EXPR, c, temp, 0));
}