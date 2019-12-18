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
 scalar_t__ CONST0_RTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_FLOAT ; 

int
s390_float_const_zero_p (rtx value)
{
  return (GET_MODE_CLASS (GET_MODE (value)) == MODE_FLOAT
	  && value == CONST0_RTX (GET_MODE (value)));
}