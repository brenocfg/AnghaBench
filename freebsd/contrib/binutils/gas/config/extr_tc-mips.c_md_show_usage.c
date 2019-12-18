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
struct TYPE_2__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 TYPE_1__* mips_cpu_info_table ; 
 int /*<<< orphan*/  show (int /*<<< orphan*/ *,char*,int*,int*) ; 

void
md_show_usage (FILE *stream)
{
  int column, first;
  size_t i;

  fprintf (stream, _("\
MIPS options:\n\
-EB			generate big endian output\n\
-EL			generate little endian output\n\
-g, -g2			do not remove unneeded NOPs or swap branches\n\
-G NUM			allow referencing objects up to NUM bytes\n\
			implicitly with the gp register [default 8]\n"));
  fprintf (stream, _("\
-mips1			generate MIPS ISA I instructions\n\
-mips2			generate MIPS ISA II instructions\n\
-mips3			generate MIPS ISA III instructions\n\
-mips4			generate MIPS ISA IV instructions\n\
-mips5                  generate MIPS ISA V instructions\n\
-mips32                 generate MIPS32 ISA instructions\n\
-mips32r2               generate MIPS32 release 2 ISA instructions\n\
-mips64                 generate MIPS64 ISA instructions\n\
-mips64r2               generate MIPS64 release 2 ISA instructions\n\
-march=CPU/-mtune=CPU	generate code/schedule for CPU, where CPU is one of:\n"));

  first = 1;

  for (i = 0; mips_cpu_info_table[i].name != NULL; i++)
    show (stream, mips_cpu_info_table[i].name, &column, &first);
  show (stream, "from-abi", &column, &first);
  fputc ('\n', stream);

  fprintf (stream, _("\
-mCPU			equivalent to -march=CPU -mtune=CPU. Deprecated.\n\
-no-mCPU		don't generate code specific to CPU.\n\
			For -mCPU and -no-mCPU, CPU must be one of:\n"));

  first = 1;

  show (stream, "3900", &column, &first);
  show (stream, "4010", &column, &first);
  show (stream, "4100", &column, &first);
  show (stream, "4650", &column, &first);
  fputc ('\n', stream);

  fprintf (stream, _("\
-mips16			generate mips16 instructions\n\
-no-mips16		do not generate mips16 instructions\n"));
  fprintf (stream, _("\
-msmartmips		generate smartmips instructions\n\
-mno-smartmips		do not generate smartmips instructions\n"));  
  fprintf (stream, _("\
-mdsp			generate DSP instructions\n\
-mno-dsp		do not generate DSP instructions\n"));
  fprintf (stream, _("\
-mdspr2			generate DSP R2 instructions\n\
-mno-dspr2		do not generate DSP R2 instructions\n"));
  fprintf (stream, _("\
-mmt			generate MT instructions\n\
-mno-mt			do not generate MT instructions\n"));
  fprintf (stream, _("\
-mfix-vr4120		work around certain VR4120 errata\n\
-mfix-vr4130		work around VR4130 mflo/mfhi errata\n\
-mgp32			use 32-bit GPRs, regardless of the chosen ISA\n\
-mfp32			use 32-bit FPRs, regardless of the chosen ISA\n\
-msym32			assume all symbols have 32-bit values\n\
-O0			remove unneeded NOPs, do not swap branches\n\
-O			remove unneeded NOPs and swap branches\n\
--[no-]construct-floats [dis]allow floating point values to be constructed\n\
--trap, --no-break	trap exception on div by 0 and mult overflow\n\
--break, --no-trap	break exception on div by 0 and mult overflow\n"));
#ifdef OBJ_ELF
  fprintf (stream, _("\
-KPIC, -call_shared	generate SVR4 position independent code\n\
-mvxworks-pic		generate VxWorks position independent code\n\
-non_shared		do not generate position independent code\n\
-xgot			assume a 32 bit GOT\n\
-mpdr, -mno-pdr		enable/disable creation of .pdr sections\n\
-mshared, -mno-shared   disable/enable .cpload optimization for\n\
                        position dependent (non shared) code\n\
-mabi=ABI		create ABI conformant object file for:\n"));

  first = 1;

  show (stream, "32", &column, &first);
  show (stream, "o64", &column, &first);
  show (stream, "n32", &column, &first);
  show (stream, "64", &column, &first);
  show (stream, "eabi", &column, &first);

  fputc ('\n', stream);

  fprintf (stream, _("\
-32			create o32 ABI object file (default)\n\
-n32			create n32 ABI object file\n\
-64			create 64 ABI object file\n"));
#endif
  fprintf (stream, _("\
-mocteon-unsupported    error on unsupported Octeon instructions\n\
-mno-octeon-unsupported do not error on unsupported Octeon instructions\n"));
  fprintf (stream, _("\
-mocteon-useun    generate Octeon unaligned load/store instructions\n\
-mno-octeon-useun generate MIPS unaligned load/store instructions\n"));
}