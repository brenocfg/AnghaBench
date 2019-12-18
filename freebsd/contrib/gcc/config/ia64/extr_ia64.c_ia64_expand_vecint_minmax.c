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
 int GT ; 
 int GTU ; 
 int LT ; 
 int LTU ; 
#define  SMAX 131 
#define  SMIN 130 
#define  UMAX 129 
#define  UMIN 128 
 int V4HImode ; 
 int V8QImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_addv4hi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_US_MINUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_expand_vecint_cmov (int /*<<< orphan*/ *) ; 

bool
ia64_expand_vecint_minmax (enum rtx_code code, enum machine_mode mode,
			   rtx operands[])
{
  rtx xops[6];

  /* These four combinations are supported directly.  */
  if (mode == V8QImode && (code == UMIN || code == UMAX))
    return false;
  if (mode == V4HImode && (code == SMIN || code == SMAX))
    return false;

  /* This combination can be implemented with only saturating subtraction.  */
  if (mode == V4HImode && code == UMAX)
    {
      rtx x, tmp = gen_reg_rtx (mode);

      x = gen_rtx_US_MINUS (mode, operands[1], operands[2]);
      emit_insn (gen_rtx_SET (VOIDmode, tmp, x));

      emit_insn (gen_addv4hi3 (operands[0], tmp, operands[2]));
      return true;
    }

  /* Everything else implemented via vector comparisons.  */
  xops[0] = operands[0];
  xops[4] = xops[1] = operands[1];
  xops[5] = xops[2] = operands[2];

  switch (code)
    {
    case UMIN:
      code = LTU;
      break;
    case UMAX:
      code = GTU;
      break;
    case SMIN:
      code = LT;
      break;
    case SMAX:
      code = GT;
      break;
    default:
      gcc_unreachable ();
    }
  xops[3] = gen_rtx_fmt_ee (code, VOIDmode, operands[1], operands[2]);

  ia64_expand_vecint_cmov (xops);
  return true;
}