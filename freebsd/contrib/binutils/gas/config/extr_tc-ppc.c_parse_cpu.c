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
 int PPC_OPCODE_403 ; 
 int PPC_OPCODE_440 ; 
 int PPC_OPCODE_601 ; 
 int PPC_OPCODE_64 ; 
 int PPC_OPCODE_64_BRIDGE ; 
 int PPC_OPCODE_ALTIVEC ; 
 int PPC_OPCODE_ANY ; 
 int PPC_OPCODE_BOOKE ; 
 int PPC_OPCODE_BOOKE64 ; 
 int PPC_OPCODE_BRLOCK ; 
 int PPC_OPCODE_CACHELCK ; 
 int PPC_OPCODE_CELL ; 
 int PPC_OPCODE_CLASSIC ; 
 int PPC_OPCODE_COMMON ; 
 int PPC_OPCODE_E300 ; 
 int PPC_OPCODE_EFS ; 
 int PPC_OPCODE_ISEL ; 
 int PPC_OPCODE_PMR ; 
 int PPC_OPCODE_POWER ; 
 int PPC_OPCODE_POWER2 ; 
 int PPC_OPCODE_POWER4 ; 
 int PPC_OPCODE_POWER5 ; 
 int PPC_OPCODE_POWER6 ; 
 int PPC_OPCODE_PPC ; 
 int PPC_OPCODE_RFMCI ; 
 int PPC_OPCODE_SPE ; 
 int ppc_cpu ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
parse_cpu (const char *arg)
{
  /* -mpwrx and -mpwr2 mean to assemble for the IBM POWER/2
     (RIOS2).  */
  if (strcmp (arg, "pwrx") == 0 || strcmp (arg, "pwr2") == 0)
    ppc_cpu = PPC_OPCODE_POWER | PPC_OPCODE_POWER2 | PPC_OPCODE_32;
  /* -mpwr means to assemble for the IBM POWER (RIOS1).  */
  else if (strcmp (arg, "pwr") == 0)
    ppc_cpu = PPC_OPCODE_POWER | PPC_OPCODE_32;
  /* -m601 means to assemble for the PowerPC 601, which includes
     instructions that are holdovers from the Power.  */
  else if (strcmp (arg, "601") == 0)
    ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
	       | PPC_OPCODE_601 | PPC_OPCODE_32);
  /* -mppc, -mppc32, -m603, and -m604 mean to assemble for the
     PowerPC 603/604.  */
  else if (strcmp (arg, "ppc") == 0
	   || strcmp (arg, "ppc32") == 0
	   || strcmp (arg, "603") == 0
	   || strcmp (arg, "604") == 0)
    ppc_cpu = PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC | PPC_OPCODE_32;
  /* -m403 and -m405 mean to assemble for the PowerPC 403/405.  */
  else if (strcmp (arg, "403") == 0
	   || strcmp (arg, "405") == 0)
    ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
	       | PPC_OPCODE_403 | PPC_OPCODE_32);
  else if (strcmp (arg, "440") == 0)
    ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_BOOKE | PPC_OPCODE_32
	       | PPC_OPCODE_440 | PPC_OPCODE_ISEL | PPC_OPCODE_RFMCI);
  else if (strcmp (arg, "7400") == 0
	   || strcmp (arg, "7410") == 0
	   || strcmp (arg, "7450") == 0
	   || strcmp (arg, "7455") == 0)
    ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
	       | PPC_OPCODE_ALTIVEC | PPC_OPCODE_32);
  else if (strcmp (arg, "e300") == 0)
    ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC | PPC_OPCODE_32
	       | PPC_OPCODE_E300);
  else if (strcmp (arg, "altivec") == 0)
    {
      if (ppc_cpu == 0)
	ppc_cpu = PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC | PPC_OPCODE_ALTIVEC;
      else
	ppc_cpu |= PPC_OPCODE_ALTIVEC;
    }
  else if (strcmp (arg, "e500") == 0 || strcmp (arg, "e500x2") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_BOOKE | PPC_OPCODE_SPE
		 | PPC_OPCODE_ISEL | PPC_OPCODE_EFS | PPC_OPCODE_BRLOCK
		 | PPC_OPCODE_PMR | PPC_OPCODE_CACHELCK
		 | PPC_OPCODE_RFMCI);
    }
  else if (strcmp (arg, "spe") == 0)
    {
      if (ppc_cpu == 0)
	ppc_cpu = PPC_OPCODE_PPC | PPC_OPCODE_SPE | PPC_OPCODE_EFS;
      else
	ppc_cpu |= PPC_OPCODE_SPE;
    }
  /* -mppc64 and -m620 mean to assemble for the 64-bit PowerPC
     620.  */
  else if (strcmp (arg, "ppc64") == 0 || strcmp (arg, "620") == 0)
    {
      ppc_cpu = PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC | PPC_OPCODE_64;
    }
  else if (strcmp (arg, "ppc64bridge") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
		 | PPC_OPCODE_64_BRIDGE | PPC_OPCODE_64);
    }
  /* -mbooke/-mbooke32 mean enable 32-bit BookE support.  */
  else if (strcmp (arg, "booke") == 0 || strcmp (arg, "booke32") == 0)
    {
      ppc_cpu = PPC_OPCODE_PPC | PPC_OPCODE_BOOKE | PPC_OPCODE_32;
    }
  /* -mbooke64 means enable 64-bit BookE support.  */
  else if (strcmp (arg, "booke64") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_BOOKE
		 | PPC_OPCODE_BOOKE64 | PPC_OPCODE_64);
    }
  else if (strcmp (arg, "power4") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
		 | PPC_OPCODE_64 | PPC_OPCODE_POWER4);
    }
  else if (strcmp (arg, "power5") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
		 | PPC_OPCODE_64 | PPC_OPCODE_POWER4
		 | PPC_OPCODE_POWER5);
    }
  else if (strcmp (arg, "power6") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
		 | PPC_OPCODE_64 | PPC_OPCODE_POWER4
		 | PPC_OPCODE_POWER5 | PPC_OPCODE_POWER6);
    }
  else if (strcmp (arg, "cell") == 0)
    {
      ppc_cpu = (PPC_OPCODE_PPC | PPC_OPCODE_CLASSIC
		 | PPC_OPCODE_64 | PPC_OPCODE_POWER4
		 | PPC_OPCODE_CELL);
    }
  /* -mcom means assemble for the common intersection between Power
     and PowerPC.  At present, we just allow the union, rather
     than the intersection.  */
  else if (strcmp (arg, "com") == 0)
    ppc_cpu = PPC_OPCODE_COMMON | PPC_OPCODE_32;
  /* -many means to assemble for any architecture (PWR/PWRX/PPC).  */
  else if (strcmp (arg, "any") == 0)
    ppc_cpu |= PPC_OPCODE_ANY;
  else
    return 0;

  return 1;
}