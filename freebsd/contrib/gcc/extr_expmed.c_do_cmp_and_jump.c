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
 int GEU ; 
 int GTU ; 
 int LEU ; 
 int LTU ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  do_compare_rtx_and_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_cmp_and_jump (rtx arg1, rtx arg2, enum rtx_code op, enum machine_mode mode,
		 rtx label)
{
  int unsignedp = (op == LTU || op == LEU || op == GTU || op == GEU);
  do_compare_rtx_and_jump (arg1, arg2, op, unsignedp, mode,
			   NULL_RTX, NULL_RTX, label);
}