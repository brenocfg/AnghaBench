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
 size_t DEPRECATED_REGISTER_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP0_REGNUM ; 
 int /*<<< orphan*/  FPC_REGNUM ; 
 int MC68K_FPREG_PLEN ; 
 int MC68K_FPREG_SIZE ; 
 int MC68K_GREG_PLEN ; 
 int MC68K_GREG_SIZE ; 
 size_t MC68K_R_D0 ; 
 size_t MC68K_R_FP0 ; 
 size_t MC68K_R_FPCR ; 
 size_t MC68K_R_PC ; 
 size_t MC68K_R_SR ; 
 int /*<<< orphan*/  PC_REGNUM ; 
 int /*<<< orphan*/  PS_REGNUM ; 
 int /*<<< orphan*/  PTRACE_GETFPREGS ; 
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * deprecated_registers ; 
 int /*<<< orphan*/  deprecated_registers_fetched () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_read_registers (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ target_has_fp ; 

void
vx_read_register (int regno)
{
  char mc68k_greg_packet[MC68K_GREG_PLEN];
  char mc68k_fpreg_packet[MC68K_FPREG_PLEN];

  /* Get general-purpose registers.  */

  net_read_registers (mc68k_greg_packet, MC68K_GREG_PLEN, PTRACE_GETREGS);

  bcopy (&mc68k_greg_packet[MC68K_R_D0], deprecated_registers,
	 16 * MC68K_GREG_SIZE);
  bcopy (&mc68k_greg_packet[MC68K_R_SR],
	 &deprecated_registers[DEPRECATED_REGISTER_BYTE (PS_REGNUM)],
	 MC68K_GREG_SIZE);
  bcopy (&mc68k_greg_packet[MC68K_R_PC],
	 &deprecated_registers[DEPRECATED_REGISTER_BYTE (PC_REGNUM)],
	 MC68K_GREG_SIZE);

  /* Get floating-point registers, if the target system has them.
     Otherwise, zero them.  */

  if (target_has_fp)
    {
      net_read_registers (mc68k_fpreg_packet, MC68K_FPREG_PLEN,
			  PTRACE_GETFPREGS);

      bcopy (&mc68k_fpreg_packet[MC68K_R_FP0],
	     &deprecated_registers[DEPRECATED_REGISTER_BYTE (FP0_REGNUM)],
	     MC68K_FPREG_SIZE * 8);
      bcopy (&mc68k_fpreg_packet[MC68K_R_FPCR],
	     &deprecated_registers[DEPRECATED_REGISTER_BYTE (FPC_REGNUM)],
	     MC68K_FPREG_PLEN - (MC68K_FPREG_SIZE * 8));
    }
  else
    {
      memset (&deprecated_registers[DEPRECATED_REGISTER_BYTE (FP0_REGNUM)],
	      0, MC68K_FPREG_SIZE * 8);
      memset (&deprecated_registers[DEPRECATED_REGISTER_BYTE (FPC_REGNUM)],
	      0, MC68K_FPREG_PLEN - (MC68K_FPREG_SIZE * 8));
    }

  /* Mark the register cache valid.  */

  deprecated_registers_fetched ();
}