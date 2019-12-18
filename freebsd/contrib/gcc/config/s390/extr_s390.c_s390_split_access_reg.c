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
 int ACCESS_REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DImode ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int TARGET_64BIT ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 

void
s390_split_access_reg (rtx reg, rtx *lo, rtx *hi)
{
  gcc_assert (TARGET_64BIT);
  gcc_assert (ACCESS_REG_P (reg));
  gcc_assert (GET_MODE (reg) == DImode);
  gcc_assert (!(REGNO (reg) & 1));

  *lo = gen_rtx_REG (SImode, REGNO (reg) + 1);
  *hi = gen_rtx_REG (SImode, REGNO (reg));
}