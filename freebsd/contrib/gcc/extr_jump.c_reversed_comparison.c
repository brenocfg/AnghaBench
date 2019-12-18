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
 int /*<<< orphan*/  NULL_RTX ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int reversed_comparison_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_relational (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
reversed_comparison (rtx exp, enum machine_mode mode)
{
  enum rtx_code reversed_code = reversed_comparison_code (exp, NULL_RTX);
  if (reversed_code == UNKNOWN)
    return NULL_RTX;
  else
    return simplify_gen_relational (reversed_code, mode, VOIDmode,
                                    XEXP (exp, 0), XEXP (exp, 1));
}