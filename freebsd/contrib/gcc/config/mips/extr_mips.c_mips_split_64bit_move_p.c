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
 scalar_t__ FP_REG_RTX_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_64BIT ; 
 int mips_isa ; 

bool
mips_split_64bit_move_p (rtx dest, rtx src)
{
  if (TARGET_64BIT)
    return false;

  /* FP->FP moves can be done in a single instruction.  */
  if (FP_REG_RTX_P (src) && FP_REG_RTX_P (dest))
    return false;

  /* Check for floating-point loads and stores.  They can be done using
     ldc1 and sdc1 on MIPS II and above.  */
  if (mips_isa > 1)
    {
      if (FP_REG_RTX_P (dest) && MEM_P (src))
	return false;
      if (FP_REG_RTX_P (src) && MEM_P (dest))
	return false;
    }
  return true;
}