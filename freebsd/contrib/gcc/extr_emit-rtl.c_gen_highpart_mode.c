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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_highpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_subreg (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreg_highpart_offset (int,int) ; 

rtx
gen_highpart_mode (enum machine_mode outermode, enum machine_mode innermode, rtx exp)
{
  if (GET_MODE (exp) != VOIDmode)
    {
      gcc_assert (GET_MODE (exp) == innermode);
      return gen_highpart (outermode, exp);
    }
  return simplify_gen_subreg (outermode, exp, innermode,
			      subreg_highpart_offset (outermode, innermode));
}