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
typedef  int /*<<< orphan*/  rtvec ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int LT ; 
 int SMAX ; 
 int SMIN ; 
 int UNGE ; 
 int UNSPEC_IEEE_MAX ; 
 int UNSPEC_IEEE_MIN ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_finite_math_only ; 
 int /*<<< orphan*/  flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ix86_expand_sse_fp_minmax (rtx dest, enum rtx_code code, rtx cmp_op0,
			   rtx cmp_op1, rtx if_true, rtx if_false)
{
  enum machine_mode mode;
  bool is_min;
  rtx tmp;

  if (code == LT)
    ;
  else if (code == UNGE)
    {
      tmp = if_true;
      if_true = if_false;
      if_false = tmp;
    }
  else
    return false;

  if (rtx_equal_p (cmp_op0, if_true) && rtx_equal_p (cmp_op1, if_false))
    is_min = true;
  else if (rtx_equal_p (cmp_op1, if_true) && rtx_equal_p (cmp_op0, if_false))
    is_min = false;
  else
    return false;

  mode = GET_MODE (dest);

  /* We want to check HONOR_NANS and HONOR_SIGNED_ZEROS here,
     but MODE may be a vector mode and thus not appropriate.  */
  if (!flag_finite_math_only || !flag_unsafe_math_optimizations)
    {
      int u = is_min ? UNSPEC_IEEE_MIN : UNSPEC_IEEE_MAX;
      rtvec v;

      if_true = force_reg (mode, if_true);
      v = gen_rtvec (2, if_true, if_false);
      tmp = gen_rtx_UNSPEC (mode, v, u);
    }
  else
    {
      code = is_min ? SMIN : SMAX;
      tmp = gen_rtx_fmt_ee (code, mode, if_true, if_false);
    }

  emit_insn (gen_rtx_SET (VOIDmode, dest, tmp));
  return true;
}