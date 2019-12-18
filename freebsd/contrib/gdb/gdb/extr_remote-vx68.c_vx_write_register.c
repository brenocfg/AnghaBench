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
 int /*<<< orphan*/  PTRACE_SETFPREGS ; 
 int /*<<< orphan*/  PTRACE_SETREGS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * deprecated_registers ; 
 int /*<<< orphan*/  net_write_registers (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ target_has_fp ; 

void
vx_write_register (int regno)
{
  char mc68k_greg_packet[MC68K_GREG_PLEN];
  char mc68k_fpreg_packet[MC68K_FPREG_PLEN];

  /* Store general-purpose registers.  */

  bcopy (deprecated_registers, &mc68k_greg_packet[MC68K_R_D0],
	 16 * MC68K_GREG_SIZE);
  bcopy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (PS_REGNUM)],
	 &mc68k_greg_packet[MC68K_R_SR], MC68K_GREG_SIZE);
  bcopy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (PC_REGNUM)],
	 &mc68k_greg_packet[MC68K_R_PC], MC68K_GREG_SIZE);

  net_write_registers (mc68k_greg_packet, MC68K_GREG_PLEN, PTRACE_SETREGS);

  /* Store floating point registers if the target has them.  */

  if (target_has_fp)
    {
      bcopy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (FP0_REGNUM)],
	     &mc68k_fpreg_packet[MC68K_R_FP0],
	     MC68K_FPREG_SIZE * 8);
      bcopy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (FPC_REGNUM)],
	     &mc68k_fpreg_packet[MC68K_R_FPCR],
	     MC68K_FPREG_PLEN - (MC68K_FPREG_SIZE * 8));

      net_write_registers (mc68k_fpreg_packet, MC68K_FPREG_PLEN,
			   PTRACE_SETFPREGS);
    }
}