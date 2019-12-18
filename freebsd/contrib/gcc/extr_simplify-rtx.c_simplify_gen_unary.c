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
 int /*<<< orphan*/  gen_rtx_fmt_e (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_unary_operation (int,int,int /*<<< orphan*/ ,int) ; 

rtx
simplify_gen_unary (enum rtx_code code, enum machine_mode mode, rtx op,
		    enum machine_mode op_mode)
{
  rtx tem;

  /* If this simplifies, use it.  */
  if ((tem = simplify_unary_operation (code, mode, op, op_mode)) != 0)
    return tem;

  return gen_rtx_fmt_e (code, mode, op);
}