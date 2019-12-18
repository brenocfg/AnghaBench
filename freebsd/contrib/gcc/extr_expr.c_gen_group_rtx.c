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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* alloca (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec_v (int,scalar_t__*) ; 
 scalar_t__ gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 

rtx
gen_group_rtx (rtx orig)
{
  int i, length;
  rtx *tmps;

  gcc_assert (GET_CODE (orig) == PARALLEL);

  length = XVECLEN (orig, 0);
  tmps = alloca (sizeof (rtx) * length);

  /* Skip a NULL entry in first slot.  */
  i = XEXP (XVECEXP (orig, 0, 0), 0) ? 0 : 1;

  if (i)
    tmps[0] = 0;

  for (; i < length; i++)
    {
      enum machine_mode mode = GET_MODE (XEXP (XVECEXP (orig, 0, i), 0));
      rtx offset = XEXP (XVECEXP (orig, 0, i), 1);

      tmps[i] = gen_rtx_EXPR_LIST (VOIDmode, gen_reg_rtx (mode), offset);
    }

  return gen_rtx_PARALLEL (GET_MODE (orig), gen_rtvec_v (length, tmps));
}