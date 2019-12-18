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
struct TYPE_2__ {scalar_t__ arch; int mach; } ;

/* Variables and functions */
 int NUM_REALREGS ; 
 int NUM_REGS ; 
 TYPE_1__* TARGET_ARCHITECTURE ; 
 scalar_t__ bfd_arch_h8300 ; 
 scalar_t__ bfd_arch_sh ; 
#define  bfd_mach_h8300s 134 
#define  bfd_mach_h8300sn 133 
#define  bfd_mach_h8300sx 132 
#define  bfd_mach_h8300sxn 131 
#define  bfd_mach_sh3 130 
#define  bfd_mach_sh3e 129 
#define  bfd_mach_sh4 128 
 int /*<<< orphan*/  fetch_regs_from_dump (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gch ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 
 char* want_h8300h ; 
 char* want_h8300s ; 
 char* want_sh ; 
 char* want_sh3 ; 

__attribute__((used)) static void
e7000_fetch_registers (void)
{
  int regno;
  char *wanted = NULL;

  puts_e7000debug ("R\r");

  if (TARGET_ARCHITECTURE->arch == bfd_arch_sh)
    {
      wanted = want_sh;
      switch (TARGET_ARCHITECTURE->mach)
	{
	case bfd_mach_sh3:
	case bfd_mach_sh3e:
	case bfd_mach_sh4:
	  wanted = want_sh3;
	}
    }
  if (TARGET_ARCHITECTURE->arch == bfd_arch_h8300)
    {
      wanted = want_h8300h;
      switch (TARGET_ARCHITECTURE->mach)
	{
	case bfd_mach_h8300s:
	case bfd_mach_h8300sn:
	case bfd_mach_h8300sx:
	case bfd_mach_h8300sxn:
	  wanted = want_h8300s;
	}
    }

  fetch_regs_from_dump (gch, wanted);

  /* And supply the extra ones the simulator uses */
  for (regno = NUM_REALREGS; regno < NUM_REGS; regno++)
    {
      int buf = 0;

      supply_register (regno, (char *) (&buf));
    }
}