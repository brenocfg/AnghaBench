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
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_relational_operation (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
simplify_gen_relational (enum rtx_code code, enum machine_mode mode,
			 enum machine_mode cmp_mode, rtx op0, rtx op1)
{
  rtx tem;

  if (0 != (tem = simplify_relational_operation (code, mode, cmp_mode,
						 op0, op1)))
    return tem;

  return gen_rtx_fmt_ee (code, mode, op0, op1);
}