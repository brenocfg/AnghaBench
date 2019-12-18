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
typedef  int /*<<< orphan*/  rtvec ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (int) ; 
 scalar_t__ CONST1_RTX (int) ; 
 int GET_MODE_INNER (int) ; 
 int GET_MODE_NUNITS (int) ; 
 scalar_t__ RTVEC_ELT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_rtx_raw_CONST_VECTOR (int,int /*<<< orphan*/ ) ; 

rtx
gen_rtx_CONST_VECTOR (enum machine_mode mode, rtvec v)
{
  enum machine_mode inner = GET_MODE_INNER (mode);
  int nunits = GET_MODE_NUNITS (mode);
  rtx x;
  int i;

  /* Check to see if all of the elements have the same value.  */
  x = RTVEC_ELT (v, nunits - 1);
  for (i = nunits - 2; i >= 0; i--)
    if (RTVEC_ELT (v, i) != x)
      break;

  /* If the values are all the same, check to see if we can use one of the
     standard constant vectors.  */
  if (i == -1)
    {
      if (x == CONST0_RTX (inner))
	return CONST0_RTX (mode);
      else if (x == CONST1_RTX (inner))
	return CONST1_RTX (mode);
    }

  return gen_rtx_raw_CONST_VECTOR (mode, v);
}