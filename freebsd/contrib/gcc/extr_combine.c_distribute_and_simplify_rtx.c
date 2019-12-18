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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int AND ; 
 int /*<<< orphan*/  ARITHMETIC_P (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int IOR ; 
 scalar_t__ NOT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int XOR ; 
 int /*<<< orphan*/  apply_distributive_law (int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_binary (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
distribute_and_simplify_rtx (rtx x, int n)
{
  enum machine_mode mode;
  enum rtx_code outer_code, inner_code;
  rtx decomposed, distributed, inner_op0, inner_op1, new_op0, new_op1, tmp;

  decomposed = XEXP (x, n);
  if (!ARITHMETIC_P (decomposed))
    return NULL_RTX;

  mode = GET_MODE (x);
  outer_code = GET_CODE (x);
  distributed = XEXP (x, !n);

  inner_code = GET_CODE (decomposed);
  inner_op0 = XEXP (decomposed, 0);
  inner_op1 = XEXP (decomposed, 1);

  /* Special case (and (xor B C) (not A)), which is equivalent to
     (xor (ior A B) (ior A C))  */
  if (outer_code == AND && inner_code == XOR && GET_CODE (distributed) == NOT)
    {
      distributed = XEXP (distributed, 0);
      outer_code = IOR;
    }

  if (n == 0)
    {
      /* Distribute the second term.  */
      new_op0 = simplify_gen_binary (outer_code, mode, inner_op0, distributed);
      new_op1 = simplify_gen_binary (outer_code, mode, inner_op1, distributed);
    }
  else
    {
      /* Distribute the first term.  */
      new_op0 = simplify_gen_binary (outer_code, mode, distributed, inner_op0);
      new_op1 = simplify_gen_binary (outer_code, mode, distributed, inner_op1);
    }

  tmp = apply_distributive_law (simplify_gen_binary (inner_code, mode,
						     new_op0, new_op1));
  if (GET_CODE (tmp) != outer_code
      && rtx_cost (tmp, SET) < rtx_cost (x, SET))
    return tmp;

  return NULL_RTX;
}