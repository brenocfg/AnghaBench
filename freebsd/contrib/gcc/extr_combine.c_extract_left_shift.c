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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  AND 134 
#define  ASHIFT 133 
 int CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  IOR 132 
#define  NEG 131 
#define  NOT 130 
 int /*<<< orphan*/  NULL_RTX ; 
#define  PLUS 129 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
#define  XOR 128 
 int /*<<< orphan*/  simplify_gen_binary (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_unary (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simplify_shift_const (int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
extract_left_shift (rtx x, int count)
{
  enum rtx_code code = GET_CODE (x);
  enum machine_mode mode = GET_MODE (x);
  rtx tem;

  switch (code)
    {
    case ASHIFT:
      /* This is the shift itself.  If it is wide enough, we will return
	 either the value being shifted if the shift count is equal to
	 COUNT or a shift for the difference.  */
      if (GET_CODE (XEXP (x, 1)) == CONST_INT
	  && INTVAL (XEXP (x, 1)) >= count)
	return simplify_shift_const (NULL_RTX, ASHIFT, mode, XEXP (x, 0),
				     INTVAL (XEXP (x, 1)) - count);
      break;

    case NEG:  case NOT:
      if ((tem = extract_left_shift (XEXP (x, 0), count)) != 0)
	return simplify_gen_unary (code, mode, tem, mode);

      break;

    case PLUS:  case IOR:  case XOR:  case AND:
      /* If we can safely shift this constant and we find the inner shift,
	 make a new operation.  */
      if (GET_CODE (XEXP (x, 1)) == CONST_INT
	  && (INTVAL (XEXP (x, 1)) & ((((HOST_WIDE_INT) 1 << count)) - 1)) == 0
	  && (tem = extract_left_shift (XEXP (x, 0), count)) != 0)
	return simplify_gen_binary (code, mode, tem,
				    GEN_INT (INTVAL (XEXP (x, 1)) >> count));

      break;

    default:
      break;
    }

  return 0;
}