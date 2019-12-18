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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRULY_NOOP_TRUNCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtx_cost (int /*<<< orphan*/ ,int) ; 
 scalar_t__ subreg_lowpart_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
notreg_cost (rtx x, enum rtx_code outer)
{
  return ((GET_CODE (x) == SUBREG
	   && REG_P (SUBREG_REG (x))
	   && GET_MODE_CLASS (GET_MODE (x)) == MODE_INT
	   && GET_MODE_CLASS (GET_MODE (SUBREG_REG (x))) == MODE_INT
	   && (GET_MODE_SIZE (GET_MODE (x))
	       < GET_MODE_SIZE (GET_MODE (SUBREG_REG (x))))
	   && subreg_lowpart_p (x)
	   && TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (GET_MODE (x)),
				     GET_MODE_BITSIZE (GET_MODE (SUBREG_REG (x)))))
	  ? 0
	  : rtx_cost (x, outer) * 2);
}