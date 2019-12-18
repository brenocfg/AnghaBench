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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/  const,unsigned int) ; 
 unsigned int end_hard_regno (int,unsigned int) ; 

__attribute__((used)) static inline bool
overlaps_hard_reg_set_p (const HARD_REG_SET regs, enum machine_mode mode,
			 unsigned int regno)
{
  unsigned int end_regno;

  if (TEST_HARD_REG_BIT (regs, regno))
    return true;

  end_regno = end_hard_regno (mode, regno);
  while (++regno < end_regno)
    if (TEST_HARD_REG_BIT (regs, regno))
      return true;

  return false;
}