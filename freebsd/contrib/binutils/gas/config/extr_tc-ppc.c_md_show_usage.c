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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
md_show_usage (FILE *stream)
{
  fprintf (stream, _("\
PowerPC options:\n\
-a32			generate ELF32/XCOFF32\n\
-a64			generate ELF64/XCOFF64\n\
-u			ignored\n\
-mpwrx, -mpwr2		generate code for POWER/2 (RIOS2)\n\
-mpwr			generate code for POWER (RIOS1)\n\
-m601			generate code for PowerPC 601\n\
-mppc, -mppc32, -m603, -m604\n\
			generate code for PowerPC 603/604\n\
-m403, -m405		generate code for PowerPC 403/405\n\
-m440			generate code for PowerPC 440\n\
-m7400, -m7410, -m7450, -m7455\n\
			generate code For PowerPC 7400/7410/7450/7455\n"));
  fprintf (stream, _("\
-mppc64, -m620		generate code for PowerPC 620/625/630\n\
-mppc64bridge		generate code for PowerPC 64, including bridge insns\n\
-mbooke64		generate code for 64-bit PowerPC BookE\n\
-mbooke, mbooke32	generate code for 32-bit PowerPC BookE\n\
-mpower4		generate code for Power4 architecture\n\
-mpower5		generate code for Power5 architecture\n\
-mpower6		generate code for Power6 architecture\n\
-mcell			generate code for Cell Broadband Engine architecture\n\
-mcom			generate code Power/PowerPC common instructions\n\
-many			generate code for any architecture (PWR/PWRX/PPC)\n"));
  fprintf (stream, _("\
-maltivec		generate code for AltiVec\n\
-me300			generate code for PowerPC e300 family\n\
-me500, -me500x2	generate code for Motorola e500 core complex\n\
-mspe			generate code for Motorola SPE instructions\n\
-mregnames		Allow symbolic names for registers\n\
-mno-regnames		Do not allow symbolic names for registers\n"));
#ifdef OBJ_ELF
  fprintf (stream, _("\
-mrelocatable		support for GCC's -mrelocatble option\n\
-mrelocatable-lib	support for GCC's -mrelocatble-lib option\n\
-memb			set PPC_EMB bit in ELF flags\n\
-mlittle, -mlittle-endian, -l, -le\n\
			generate code for a little endian machine\n\
-mbig, -mbig-endian, -b, -be\n\
			generate code for a big endian machine\n\
-msolaris		generate code for Solaris\n\
-mno-solaris		do not generate code for Solaris\n\
-V			print assembler version number\n\
-Qy, -Qn		ignored\n"));
#endif
}