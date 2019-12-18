#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int badvaddr; int cause; int fp_implementation_revision; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int DEPRECATED_FP_REGNUM ; 
 int FIRST_EMBED_REGNUM ; 
 int LAST_EMBED_REGNUM ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int PS_REGNUM ; 
 int /*<<< orphan*/  PT_WRITE_U ; 
 int ZERO_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_register (int) ; 
 unsigned int register_ptrace_addr (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
store_inferior_registers (int regno)
{
  unsigned int regaddr;
  char buf[80];

  if (regno > 0)
    {
      if (regno == ZERO_REGNUM || regno == PS_REGNUM
	  || regno == mips_regnum (current_gdbarch)->badvaddr
	  || regno == mips_regnum (current_gdbarch)->cause
	  || regno == mips_regnum (current_gdbarch)->fp_implementation_revision
	  || regno == DEPRECATED_FP_REGNUM
	  || (regno >= FIRST_EMBED_REGNUM && regno <= LAST_EMBED_REGNUM))
	return;
      regaddr = register_ptrace_addr (regno);
      errno = 0;
      ptrace (PT_WRITE_U, PIDGET (inferior_ptid), (PTRACE_ARG3_TYPE) regaddr,
	      read_register (regno));
      if (errno != 0)
	{
	  sprintf (buf, "writing register number %d", regno);
	  perror_with_name (buf);
	}
    }
  else
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	store_inferior_registers (regno);
    }
}