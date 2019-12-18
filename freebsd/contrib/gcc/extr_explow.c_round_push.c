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
typedef  int /*<<< orphan*/  rtx ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int PREFERRED_STACK_BOUNDARY ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TRUNC_DIV_EXPR ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  expand_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_divmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
round_push (rtx size)
{
  int align = PREFERRED_STACK_BOUNDARY / BITS_PER_UNIT;

  if (align == 1)
    return size;

  if (GET_CODE (size) == CONST_INT)
    {
      HOST_WIDE_INT new = (INTVAL (size) + align - 1) / align * align;

      if (INTVAL (size) != new)
	size = GEN_INT (new);
    }
  else
    {
      /* CEIL_DIV_EXPR needs to worry about the addition overflowing,
	 but we know it can't.  So add ourselves and then do
	 TRUNC_DIV_EXPR.  */
      size = expand_binop (Pmode, add_optab, size, GEN_INT (align - 1),
			   NULL_RTX, 1, OPTAB_LIB_WIDEN);
      size = expand_divmod (0, TRUNC_DIV_EXPR, Pmode, size, GEN_INT (align),
			    NULL_RTX, 1);
      size = expand_mult (Pmode, size, GEN_INT (align), NULL_RTX, 1);
    }

  return size;
}