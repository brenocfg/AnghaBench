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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;

/* Variables and functions */
 scalar_t__ FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 int FP_REGS ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GR_REGS ; 
 int LEA_REGS ; 
 int M16_REGS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ mips_dangerous_for_la25_p (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_class_subset_p (int,int) ; 

enum reg_class
mips_preferred_reload_class (rtx x, enum reg_class class)
{
  if (mips_dangerous_for_la25_p (x) && reg_class_subset_p (LEA_REGS, class))
    return LEA_REGS;

  if (TARGET_HARD_FLOAT
      && FLOAT_MODE_P (GET_MODE (x))
      && reg_class_subset_p (FP_REGS, class))
    return FP_REGS;

  if (reg_class_subset_p (GR_REGS, class))
    class = GR_REGS;

  if (TARGET_MIPS16 && reg_class_subset_p (M16_REGS, class))
    class = M16_REGS;

  return class;
}