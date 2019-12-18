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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ COMPLEX_CST ; 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ INTEGER_CST ; 
 int POINTER_SIZE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_IMAGPART (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REALPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 

int
integer_pow2p (tree expr)
{
  int prec;
  HOST_WIDE_INT high, low;

  STRIP_NOPS (expr);

  if (TREE_CODE (expr) == COMPLEX_CST
      && integer_pow2p (TREE_REALPART (expr))
      && integer_zerop (TREE_IMAGPART (expr)))
    return 1;

  if (TREE_CODE (expr) != INTEGER_CST)
    return 0;

  prec = (POINTER_TYPE_P (TREE_TYPE (expr))
	  ? POINTER_SIZE : TYPE_PRECISION (TREE_TYPE (expr)));
  high = TREE_INT_CST_HIGH (expr);
  low = TREE_INT_CST_LOW (expr);

  /* First clear all bits that are beyond the type's precision in case
     we've been sign extended.  */

  if (prec == 2 * HOST_BITS_PER_WIDE_INT)
    ;
  else if (prec > HOST_BITS_PER_WIDE_INT)
    high &= ~((HOST_WIDE_INT) (-1) << (prec - HOST_BITS_PER_WIDE_INT));
  else
    {
      high = 0;
      if (prec < HOST_BITS_PER_WIDE_INT)
	low &= ~((HOST_WIDE_INT) (-1) << prec);
    }

  if (high == 0 && low == 0)
    return 0;

  return ((high == 0 && (low & (low - 1)) == 0)
	  || (low == 0 && (high & (high - 1)) == 0));
}