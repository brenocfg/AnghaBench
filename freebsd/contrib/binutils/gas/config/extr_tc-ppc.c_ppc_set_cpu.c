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
 int PPC_OPCODE_32 ; 
 int PPC_OPCODE_64 ; 
 int PPC_OPCODE_ANY ; 
 int PPC_OPCODE_CLASSIC ; 
 int PPC_OPCODE_COMMON ; 
 int PPC_OPCODE_POWER ; 
 int PPC_OPCODE_PPC ; 
 char* TARGET_CPU ; 
 char* TARGET_OS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char const*,char const*) ; 
 int ppc_cpu ; 
 scalar_t__ ppc_obj64 ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
ppc_set_cpu (void)
{
  const char *default_os  = TARGET_OS;
  const char *default_cpu = TARGET_CPU;

  if ((ppc_cpu & ~PPC_OPCODE_ANY) == 0)
    {
      if (ppc_obj64)
	ppc_cpu |= PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC | PPC_OPCODE_64;
      else if (strncmp (default_os, "aix", 3) == 0
	       && default_os[3] >= '4' && default_os[3] <= '9')
	ppc_cpu |= PPC_OPCODE_COMMON | PPC_OPCODE_32;
      else if (strncmp (default_os, "aix3", 4) == 0)
	ppc_cpu |= PPC_OPCODE_POWER | PPC_OPCODE_32;
      else if (strcmp (default_cpu, "rs6000") == 0)
	ppc_cpu |= PPC_OPCODE_POWER | PPC_OPCODE_32;
      else if (strncmp (default_cpu, "powerpc", 7) == 0)
	ppc_cpu |= PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC | PPC_OPCODE_32;
      else
	as_fatal (_("Unknown default cpu = %s, os = %s"),
		  default_cpu, default_os);
    }
}