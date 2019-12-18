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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_PC_REGNUM ; 
 int /*<<< orphan*/  ARM_PS_REGNUM ; 
 scalar_t__ arm_apcs_32 ; 
 scalar_t__ arm_pc_is_thumb (int) ; 
 int read_register_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register_pid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_write_pc (CORE_ADDR pc, ptid_t ptid)
{
  write_register_pid (ARM_PC_REGNUM, pc, ptid);

  /* If necessary, set the T bit.  */
  if (arm_apcs_32)
    {
      CORE_ADDR val = read_register_pid (ARM_PS_REGNUM, ptid);
      if (arm_pc_is_thumb (pc))
	write_register_pid (ARM_PS_REGNUM, val | 0x20, ptid);
      else
	write_register_pid (ARM_PS_REGNUM, val & ~(CORE_ADDR) 0x20, ptid);
    }
}