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
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int DEPRECATED_FP_REGNUM ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_READ_U ; 
 int ZERO_REGNUM ; 
 int /*<<< orphan*/  deprecated_registers_fetched () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int register_ptrace_addr (int) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

void
fetch_inferior_registers (int regno)
{
  unsigned int regaddr;
  char buf[MAX_REGISTER_SIZE];
  int i;
  char zerobuf[MAX_REGISTER_SIZE];
  memset (zerobuf, 0, MAX_REGISTER_SIZE);

  deprecated_registers_fetched ();

  for (regno = 1; regno < NUM_REGS; regno++)
    {
      regaddr = register_ptrace_addr (regno);
      for (i = 0; i < DEPRECATED_REGISTER_RAW_SIZE (regno); i += sizeof (int))
	{
	  *(int *) &buf[i] = ptrace (PT_READ_U, PIDGET (inferior_ptid),
				     (PTRACE_ARG3_TYPE) regaddr, 0);
	  regaddr += sizeof (int);
	}
      supply_register (regno, buf);
    }

  supply_register (ZERO_REGNUM, zerobuf);
  /* Frame ptr reg must appear to be 0; it is faked by stack handling code. */
  supply_register (DEPRECATED_FP_REGNUM, zerobuf);
}