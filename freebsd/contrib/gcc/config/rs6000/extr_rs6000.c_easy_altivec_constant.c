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
 int GET_MODE_NUNITS (int) ; 
 int VOIDmode ; 
 scalar_t__ vspltis_constant (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

bool
easy_altivec_constant (rtx op, enum machine_mode mode)
{
  unsigned step, copies;

  if (mode == VOIDmode)
    mode = GET_MODE (op);
  else if (mode != GET_MODE (op))
    return false;

  /* Start with a vspltisw.  */
  step = GET_MODE_NUNITS (mode) / 4;
  copies = 1;

  if (vspltis_constant (op, step, copies))
    return true;

  /* Then try with a vspltish.  */
  if (step == 1)
    copies <<= 1;
  else
    step >>= 1;

  if (vspltis_constant (op, step, copies))
    return true;

  /* And finally a vspltisb.  */
  if (step == 1)
    copies <<= 1;
  else
    step >>= 1;

  if (vspltis_constant (op, step, copies))
    return true;

  return false;
}