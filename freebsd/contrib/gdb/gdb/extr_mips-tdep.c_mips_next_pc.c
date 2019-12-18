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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int mips16_next_pc (int) ; 
 int mips32_next_pc (int) ; 

CORE_ADDR
mips_next_pc (CORE_ADDR pc)
{
  if (pc & 0x01)
    return mips16_next_pc (pc);
  else
    return mips32_next_pc (pc);
}