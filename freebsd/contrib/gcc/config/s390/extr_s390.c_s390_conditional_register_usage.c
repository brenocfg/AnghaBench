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
 size_t BASE_REGNUM ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 size_t RETURN_REGNUM ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 scalar_t__ TARGET_SOFT_FLOAT ; 
 int* call_really_used_regs ; 
 int* call_used_regs ; 
 int* fixed_regs ; 
 scalar_t__ flag_pic ; 

void
s390_conditional_register_usage (void)
{
  int i;

  if (flag_pic)
    {
      fixed_regs[PIC_OFFSET_TABLE_REGNUM] = 1;
      call_used_regs[PIC_OFFSET_TABLE_REGNUM] = 1;
    }
  if (TARGET_CPU_ZARCH)
    {
      fixed_regs[BASE_REGNUM] = 0;
      call_used_regs[BASE_REGNUM] = 0;
      fixed_regs[RETURN_REGNUM] = 0;
      call_used_regs[RETURN_REGNUM] = 0;
    }
  if (TARGET_64BIT)
    {
      for (i = 24; i < 32; i++)
	call_used_regs[i] = call_really_used_regs[i] = 0;
    }
  else
    {
      for (i = 18; i < 20; i++)
	call_used_regs[i] = call_really_used_regs[i] = 0;
    }

  if (TARGET_SOFT_FLOAT)
    {
      for (i = 16; i < 32; i++)
	call_used_regs[i] = fixed_regs[i] = 1;
    }
}