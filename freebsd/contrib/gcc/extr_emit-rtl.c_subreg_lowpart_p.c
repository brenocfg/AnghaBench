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

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ subreg_lowpart_offset (scalar_t__,scalar_t__) ; 

int
subreg_lowpart_p (rtx x)
{
  if (GET_CODE (x) != SUBREG)
    return 1;
  else if (GET_MODE (SUBREG_REG (x)) == VOIDmode)
    return 0;

  return (subreg_lowpart_offset (GET_MODE (x), GET_MODE (SUBREG_REG (x)))
	  == SUBREG_BYTE (x));
}