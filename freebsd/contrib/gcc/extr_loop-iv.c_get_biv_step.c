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
struct df_ref {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (scalar_t__) ; 
 int UNKNOWN ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_biv_step_1 (struct df_ref*,scalar_t__,scalar_t__*,int*,int*,int,scalar_t__*) ; 

__attribute__((used)) static bool
get_biv_step (struct df_ref *last_def, rtx reg, rtx *inner_step,
	      enum machine_mode *inner_mode, enum rtx_code *extend,
	      enum machine_mode *outer_mode, rtx *outer_step)
{
  *outer_mode = GET_MODE (reg);

  if (!get_biv_step_1 (last_def, reg,
		       inner_step, inner_mode, extend, *outer_mode,
		       outer_step))
    return false;

  gcc_assert ((*inner_mode == *outer_mode) != (*extend != UNKNOWN));
  gcc_assert (*inner_mode != *outer_mode || *outer_step == const0_rtx);

  return true;
}