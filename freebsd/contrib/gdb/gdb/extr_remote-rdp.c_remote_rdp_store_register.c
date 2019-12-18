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
 int ARM_PC_REGNUM ; 
 int ARM_PS_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_REGS ; 
 int RDP_CPU_READWRITE_MASK_CPSR ; 
 int RDP_CPU_READWRITE_MASK_PC ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rdp_store_one_fpu_register (int,char*) ; 
 int /*<<< orphan*/  rdp_store_one_register (int,char*) ; 

__attribute__((used)) static void
remote_rdp_store_register (int regno)
{
  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	remote_rdp_store_register (regno);
    }
  else
    {
      char tmp[MAX_REGISTER_SIZE];
      deprecated_read_register_gen (regno, tmp);
      if (regno < 15)
	rdp_store_one_register (1 << regno, tmp);
      else if (regno == ARM_PC_REGNUM)
	rdp_store_one_register (RDP_CPU_READWRITE_MASK_PC, tmp);
      else if (regno == ARM_PS_REGNUM)
	rdp_store_one_register (RDP_CPU_READWRITE_MASK_CPSR, tmp);
      else if (regno >= ARM_F0_REGNUM && regno <= ARM_F7_REGNUM)
	rdp_store_one_fpu_register (1 << (regno - ARM_F0_REGNUM), tmp);
      else
	{
	  printf ("Help me with reg %d\n", regno);
	}
    }
}