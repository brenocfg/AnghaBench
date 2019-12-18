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
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ TARGET_MIPS16 ; 
 int* reg_alloc_order ; 

void
mips_order_regs_for_local_alloc (void)
{
  register int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    reg_alloc_order[i] = i;

  if (TARGET_MIPS16)
    {
      /* It really doesn't matter where we put register 0, since it is
         a fixed register anyhow.  */
      reg_alloc_order[0] = 24;
      reg_alloc_order[24] = 0;
    }
}