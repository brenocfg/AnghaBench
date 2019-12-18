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
struct TYPE_2__ {scalar_t__ arch; } ;

/* Variables and functions */
 int CCR_REGNUM ; 
 int GBR_REGNUM ; 
 int MACH_REGNUM ; 
 int MACL_REGNUM ; 
 int PC_REGNUM ; 
 int PR_REGNUM ; 
 int SR_REGNUM ; 
 TYPE_1__* TARGET_ARCHITECTURE ; 
 int VBR_REGNUM ; 
 scalar_t__ bfd_arch_h8300 ; 
 scalar_t__ bfd_arch_sh ; 
 int /*<<< orphan*/  e7000_store_registers () ; 
 int /*<<< orphan*/  expect_prompt () ; 
 char* phex_nz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int /*<<< orphan*/  read_register (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
e7000_store_register (int regno)
{
  char buf[200];

  if (regno == -1)
    {
      e7000_store_registers ();
      return;
    }

  if (TARGET_ARCHITECTURE->arch == bfd_arch_h8300)
    {
      if (regno <= 7)
	{
	  sprintf (buf, ".ER%d %s\r", regno, phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}
      else if (regno == PC_REGNUM)
	{
	  sprintf (buf, ".PC %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}
#ifdef CCR_REGNUM
      else if (regno == CCR_REGNUM)
	{
	  sprintf (buf, ".CCR %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}
#endif
    }

  else if (TARGET_ARCHITECTURE->arch == bfd_arch_sh)
    {
      if (regno == PC_REGNUM)
	{
	  sprintf (buf, ".PC %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}

      else if (regno == SR_REGNUM)
	{
	  sprintf (buf, ".SR %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}

      else if (regno ==  PR_REGNUM)
	{
	  sprintf (buf, ".PR %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}

      else if (regno == GBR_REGNUM)
	{
	  sprintf (buf, ".GBR %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}

      else if (regno == VBR_REGNUM)
	{
	  sprintf (buf, ".VBR %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}

      else if (regno == MACH_REGNUM)
	{
	  sprintf (buf, ".MACH %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}

      else if (regno == MACL_REGNUM)
	{
	  sprintf (buf, ".MACL %s\r", phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}
      else
	{
	  sprintf (buf, ".R%d %s\r", regno, phex_nz (read_register (regno), 0));
	  puts_e7000debug (buf);
	}
    }

  expect_prompt ();
}