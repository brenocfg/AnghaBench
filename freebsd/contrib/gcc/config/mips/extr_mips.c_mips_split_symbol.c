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
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_HIGH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LO_SUM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips16_gp_pseudo_reg () ; 
 int /*<<< orphan*/  mips_force_temporary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
mips_split_symbol (rtx temp, rtx addr)
{
  rtx high;

  if (TARGET_MIPS16)
    high = mips16_gp_pseudo_reg ();
  else
    high = mips_force_temporary (temp, gen_rtx_HIGH (Pmode, copy_rtx (addr)));
  return gen_rtx_LO_SUM (Pmode, high, addr);
}