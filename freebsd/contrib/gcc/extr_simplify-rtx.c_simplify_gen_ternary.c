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
 int /*<<< orphan*/  gen_rtx_fmt_eee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_ternary_operation (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
simplify_gen_ternary (enum rtx_code code, enum machine_mode mode,
		      enum machine_mode op0_mode, rtx op0, rtx op1, rtx op2)
{
  rtx tem;

  /* If this simplifies, use it.  */
  if (0 != (tem = simplify_ternary_operation (code, mode, op0_mode,
					      op0, op1, op2)))
    return tem;

  return gen_rtx_fmt_eee (code, mode, op0, op1, op2);
}