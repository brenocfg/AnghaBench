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

/* Variables and functions */
 long ia64_rse_slot_num (unsigned long*) ; 

__attribute__((used)) static inline unsigned long *
ia64_rse_skip_regs (unsigned long *addr, long num_regs)
{
  long delta = ia64_rse_slot_num (addr) + num_regs;

  if (num_regs < 0)
    delta -= 0x3e;
  return addr + num_regs + delta/0x3f;
}