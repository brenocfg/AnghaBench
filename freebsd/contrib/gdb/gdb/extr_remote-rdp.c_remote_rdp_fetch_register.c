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
 int ARM_F0_REGNUM ; 
 int ARM_F7_REGNUM ; 
 int ARM_FPS_REGNUM ; 
 int ARM_PC_REGNUM ; 
 int ARM_PS_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_REGS ; 
 int RDP_CPU_READWRITE_MASK_CPSR ; 
 int RDP_CPU_READWRITE_MASK_PC ; 
 int RDP_FPU_READWRITE_MASK_FPS ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rdp_fetch_one_fpu_register (int,char*) ; 
 int /*<<< orphan*/  rdp_fetch_one_register (int,char*) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
remote_rdp_fetch_register (int regno)
{
  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	remote_rdp_fetch_register (regno);
    }
  else
    {
      char buf[MAX_REGISTER_SIZE];
      if (regno < 15)
	rdp_fetch_one_register (1 << regno, buf);
      else if (regno == ARM_PC_REGNUM)
	rdp_fetch_one_register (RDP_CPU_READWRITE_MASK_PC, buf);
      else if (regno == ARM_PS_REGNUM)
	rdp_fetch_one_register (RDP_CPU_READWRITE_MASK_CPSR, buf);
      else if (regno == ARM_FPS_REGNUM)
	rdp_fetch_one_fpu_register (RDP_FPU_READWRITE_MASK_FPS, buf);
      else if (regno >= ARM_F0_REGNUM && regno <= ARM_F7_REGNUM)
	rdp_fetch_one_fpu_register (1 << (regno - ARM_F0_REGNUM), buf);
      else
	{
	  printf ("Help me with fetch reg %d\n", regno);
	}
      supply_register (regno, buf);
    }
}