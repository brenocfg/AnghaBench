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
typedef  int /*<<< orphan*/  optab ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum optab_methods { ____Placeholder_optab_methods } optab_methods ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/ * code_to_optab ; 
 int /*<<< orphan*/  expand_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

rtx
expand_simple_binop (enum machine_mode mode, enum rtx_code code, rtx op0,
		     rtx op1, rtx target, int unsignedp,
		     enum optab_methods methods)
{
  optab binop = code_to_optab[(int) code];
  gcc_assert (binop);

  return expand_binop (mode, binop, op0, op1, target, unsignedp, methods);
}