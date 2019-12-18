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

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reversed_comparison_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

rtx
reversed_condition (rtx cond)
{
  enum rtx_code reversed;
  reversed = reversed_comparison_code (cond, NULL);
  if (reversed == UNKNOWN)
    return NULL_RTX;
  else
    return gen_rtx_fmt_ee (reversed,
			   GET_MODE (cond), XEXP (cond, 0),
			   XEXP (cond, 1));
}