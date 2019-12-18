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

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_DOUBLE_OK_FOR_G (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ INTEGRAL_MODE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ register_operand (scalar_t__,int /*<<< orphan*/ ) ; 

int
ia64_move_ok (rtx dst, rtx src)
{
  /* If we're under init_recog_no_volatile, we'll not be able to use
     memory_operand.  So check the code directly and don't worry about
     the validity of the underlying address, which should have been
     checked elsewhere anyway.  */
  if (GET_CODE (dst) != MEM)
    return 1;
  if (GET_CODE (src) == MEM)
    return 0;
  if (register_operand (src, VOIDmode))
    return 1;

  /* Otherwise, this must be a constant, and that either 0 or 0.0 or 1.0.  */
  if (INTEGRAL_MODE_P (GET_MODE (dst)))
    return src == const0_rtx;
  else
    return GET_CODE (src) == CONST_DOUBLE && CONST_DOUBLE_OK_FOR_G (src);
}