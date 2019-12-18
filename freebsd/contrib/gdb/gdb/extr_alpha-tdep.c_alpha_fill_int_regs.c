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
 int ALPHA_PC_REGNUM ; 
 int ALPHA_UNIQUE_REGNUM ; 
 int /*<<< orphan*/  regcache_collect (int,void*) ; 

void
alpha_fill_int_regs (int regno, void *r0_r30, void *pc, void *unique)
{
  int i;

  for (i = 0; i < 31; ++i)
    if (regno == i || regno == -1)
      regcache_collect (i, (char *)r0_r30 + i*8);

  if (regno == ALPHA_PC_REGNUM || regno == -1)
    regcache_collect (ALPHA_PC_REGNUM, pc);

  if (unique && (regno == ALPHA_UNIQUE_REGNUM || regno == -1))
    regcache_collect (ALPHA_UNIQUE_REGNUM, unique);
}