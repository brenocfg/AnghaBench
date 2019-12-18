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
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;

/* Variables and functions */
 int PPC_OPCODE_ANY ; 
 int PPC_OPCODE_COMMON ; 
 int PPC_OPCODE_POWER ; 
 int PPC_OPCODE_PPC ; 
 char* TARGET_CPU ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int bfd_arch_powerpc ; 
 int bfd_arch_rs6000 ; 
 int bfd_arch_unknown ; 
 int ppc_cpu ; 
 int /*<<< orphan*/  ppc_set_cpu () ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

enum bfd_architecture
ppc_arch (void)
{
  const char *default_cpu = TARGET_CPU;
  ppc_set_cpu ();

  if ((ppc_cpu & PPC_OPCODE_PPC) != 0)
    return bfd_arch_powerpc;
  else if ((ppc_cpu & PPC_OPCODE_POWER) != 0)
    return bfd_arch_rs6000;
  else if ((ppc_cpu & (PPC_OPCODE_COMMON | PPC_OPCODE_ANY)) != 0)
    {
      if (strcmp (default_cpu, "rs6000") == 0)
	return bfd_arch_rs6000;
      else if (strncmp (default_cpu, "powerpc", 7) == 0)
	return bfd_arch_powerpc;
    }

  as_fatal (_("Neither Power nor PowerPC opcodes were selected."));
  return bfd_arch_unknown;
}