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
typedef  unsigned int CORE_ADDR ;

/* Variables and functions */
 unsigned int CORE_REGISTER_ADDR (int,unsigned int) ; 
 unsigned int KERNEL_U_ADDR ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  REGISTER_NAME (int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
fetch_core_registers (char *core_reg_sect, unsigned core_reg_size, int which,
		      CORE_ADDR reg_addr)
{
  int regno;
  CORE_ADDR addr;
  int bad_reg = -1;
  CORE_ADDR reg_ptr = -reg_addr;	/* Original u.u_ar0 is -reg_addr. */
  int numregs = NUM_REGS;

  /* If u.u_ar0 was an absolute address in the core file, relativize it now,
     so we can use it as an offset into core_reg_sect.  When we're done,
     "register 0" will be at core_reg_sect+reg_ptr, and we can use
     CORE_REGISTER_ADDR to offset to the other registers.  If this is a modern
     core file without a upage, reg_ptr will be zero and this is all a big
     NOP.  */
  if (reg_ptr > core_reg_size)
    reg_ptr -= KERNEL_U_ADDR;

  for (regno = 0; regno < numregs; regno++)
    {
      addr = CORE_REGISTER_ADDR (regno, reg_ptr);
      if (addr >= core_reg_size
	  && bad_reg < 0)
	bad_reg = regno;
      else
	supply_register (regno, core_reg_sect + addr);
    }

  if (bad_reg >= 0)
    error ("Register %s not found in core file.", REGISTER_NAME (bad_reg));
}