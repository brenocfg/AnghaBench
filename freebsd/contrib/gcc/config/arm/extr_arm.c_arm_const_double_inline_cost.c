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
 scalar_t__ CONST_INT ; 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  SImode ; 
 int VOIDmode ; 
 int arm_gen_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_highpart_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
arm_const_double_inline_cost (rtx val)
{
  rtx lowpart, highpart;
  enum machine_mode mode;

  mode = GET_MODE (val);

  if (mode == VOIDmode)
    mode = DImode;

  gcc_assert (GET_MODE_SIZE (mode) == 8);

  lowpart = gen_lowpart (SImode, val);
  highpart = gen_highpart_mode (SImode, mode, val);

  gcc_assert (GET_CODE (lowpart) == CONST_INT);
  gcc_assert (GET_CODE (highpart) == CONST_INT);

  return (arm_gen_constant (SET, SImode, NULL_RTX, INTVAL (lowpart),
			    NULL_RTX, NULL_RTX, 0, 0)
	  + arm_gen_constant (SET, SImode, NULL_RTX, INTVAL (highpart),
			      NULL_RTX, NULL_RTX, 0, 0));
}