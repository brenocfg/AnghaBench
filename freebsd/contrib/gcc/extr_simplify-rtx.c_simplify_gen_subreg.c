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
 scalar_t__ CONCAT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ SUBREG ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ gen_rtx_SUBREG (int,scalar_t__,unsigned int) ; 
 scalar_t__ simplify_subreg (int,scalar_t__,int,unsigned int) ; 
 scalar_t__ validate_subreg (int,int,scalar_t__,unsigned int) ; 

rtx
simplify_gen_subreg (enum machine_mode outermode, rtx op,
		     enum machine_mode innermode, unsigned int byte)
{
  rtx newx;

  newx = simplify_subreg (outermode, op, innermode, byte);
  if (newx)
    return newx;

  if (GET_CODE (op) == SUBREG
      || GET_CODE (op) == CONCAT
      || GET_MODE (op) == VOIDmode)
    return NULL_RTX;

  if (validate_subreg (outermode, innermode, op, byte))
    return gen_rtx_SUBREG (outermode, op, byte);

  return NULL_RTX;
}