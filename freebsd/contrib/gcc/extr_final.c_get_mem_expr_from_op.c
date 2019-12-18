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

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_RTX_CLASS (scalar_t__) ; 
 scalar_t__ MEM_EXPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ RTX_BIN_ARITH ; 
 scalar_t__ RTX_UNARY ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
get_mem_expr_from_op (rtx op, int *paddressp)
{
  tree expr;
  int inner_addressp;

  *paddressp = 0;

  if (REG_P (op))
    return REG_EXPR (op);
  else if (!MEM_P (op))
    return 0;

  if (MEM_EXPR (op) != 0)
    return MEM_EXPR (op);

  /* Otherwise we have an address, so indicate it and look at the address.  */
  *paddressp = 1;
  op = XEXP (op, 0);

  /* First check if we have a decl for the address, then look at the right side
     if it is a PLUS.  Otherwise, strip off arithmetic and keep looking.
     But don't allow the address to itself be indirect.  */
  if ((expr = get_mem_expr_from_op (op, &inner_addressp)) && ! inner_addressp)
    return expr;
  else if (GET_CODE (op) == PLUS
	   && (expr = get_mem_expr_from_op (XEXP (op, 1), &inner_addressp)))
    return expr;

  while (GET_RTX_CLASS (GET_CODE (op)) == RTX_UNARY
	 || GET_RTX_CLASS (GET_CODE (op)) == RTX_BIN_ARITH)
    op = XEXP (op, 0);

  expr = get_mem_expr_from_op (op, &inner_addressp);
  return inner_addressp ? 0 : expr;
}