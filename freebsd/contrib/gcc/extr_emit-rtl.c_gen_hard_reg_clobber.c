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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 
 scalar_t__** hard_reg_clobbers ; 

rtx
gen_hard_reg_clobber (enum machine_mode mode, unsigned int regno)
{
  if (hard_reg_clobbers[mode][regno])
    return hard_reg_clobbers[mode][regno];
  else
    return (hard_reg_clobbers[mode][regno] =
	    gen_rtx_CLOBBER (VOIDmode, gen_rtx_REG (mode, regno)));
}