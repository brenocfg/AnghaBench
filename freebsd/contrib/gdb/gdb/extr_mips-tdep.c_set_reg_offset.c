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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int NUM_REGS ; 

__attribute__((used)) static void
set_reg_offset (CORE_ADDR *saved_regs, int regno, CORE_ADDR offset)
{
  if (saved_regs[regno] == 0)
    {
      saved_regs[regno + 0 * NUM_REGS] = offset;
      saved_regs[regno + 1 * NUM_REGS] = offset;
    }
}