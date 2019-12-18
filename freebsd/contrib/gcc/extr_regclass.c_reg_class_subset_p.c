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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;

/* Variables and functions */
 int ALL_REGS ; 
 int /*<<< orphan*/  GO_IF_HARD_REG_SUBSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 int /*<<< orphan*/  win ; 

int
reg_class_subset_p (enum reg_class c1, enum reg_class c2)
{
  if (c1 == c2) return 1;

  if (c2 == ALL_REGS)
  win:
    return 1;
  GO_IF_HARD_REG_SUBSET (reg_class_contents[(int) c1],
			 reg_class_contents[(int) c2],
			 win);
  return 0;
}