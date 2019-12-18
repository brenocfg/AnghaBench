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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_CODE (int /*<<< orphan*/ *) ; 
 int GET_MODE (int /*<<< orphan*/ *) ; 
 int GET_RTX_CLASS (int) ; 
 int HIGH ; 
 int LO_SUM ; 
#define  RTX_BIN_ARITH 136 
#define  RTX_BITFIELD_OPS 135 
#define  RTX_COMM_ARITH 134 
#define  RTX_COMM_COMPARE 133 
#define  RTX_COMPARE 132 
#define  RTX_EXTRA 131 
#define  RTX_OBJ 130 
#define  RTX_TERNARY 129 
#define  RTX_UNARY 128 
 int SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SUBREG_REG (int /*<<< orphan*/ *) ; 
 int VOIDmode ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplify_binary_operation (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplify_gen_binary (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplify_gen_subreg (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * simplify_relational_operation (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplify_ternary_operation (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplify_unary_operation (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swap_commutative_operands_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

rtx
simplify_rtx (rtx x)
{
  enum rtx_code code = GET_CODE (x);
  enum machine_mode mode = GET_MODE (x);

  switch (GET_RTX_CLASS (code))
    {
    case RTX_UNARY:
      return simplify_unary_operation (code, mode,
				       XEXP (x, 0), GET_MODE (XEXP (x, 0)));
    case RTX_COMM_ARITH:
      if (swap_commutative_operands_p (XEXP (x, 0), XEXP (x, 1)))
	return simplify_gen_binary (code, mode, XEXP (x, 1), XEXP (x, 0));

      /* Fall through....  */

    case RTX_BIN_ARITH:
      return simplify_binary_operation (code, mode, XEXP (x, 0), XEXP (x, 1));

    case RTX_TERNARY:
    case RTX_BITFIELD_OPS:
      return simplify_ternary_operation (code, mode, GET_MODE (XEXP (x, 0)),
					 XEXP (x, 0), XEXP (x, 1),
					 XEXP (x, 2));

    case RTX_COMPARE:
    case RTX_COMM_COMPARE:
      return simplify_relational_operation (code, mode,
                                            ((GET_MODE (XEXP (x, 0))
                                             != VOIDmode)
                                            ? GET_MODE (XEXP (x, 0))
                                            : GET_MODE (XEXP (x, 1))),
                                            XEXP (x, 0),
                                            XEXP (x, 1));

    case RTX_EXTRA:
      if (code == SUBREG)
	return simplify_gen_subreg (mode, SUBREG_REG (x),
				    GET_MODE (SUBREG_REG (x)),
				    SUBREG_BYTE (x));
      break;

    case RTX_OBJ:
      if (code == LO_SUM)
	{
	  /* Convert (lo_sum (high FOO) FOO) to FOO.  */
	  if (GET_CODE (XEXP (x, 0)) == HIGH
	      && rtx_equal_p (XEXP (XEXP (x, 0), 0), XEXP (x, 1)))
	  return XEXP (x, 1);
	}
      break;

    default:
      break;
    }
  return NULL;
}