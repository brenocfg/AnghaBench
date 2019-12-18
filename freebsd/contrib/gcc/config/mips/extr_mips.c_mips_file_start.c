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

/* Variables and functions */
#define  ABI_32 132 
#define  ABI_64 131 
#define  ABI_EABI 130 
#define  ABI_N32 129 
#define  ABI_O64 128 
 char* ASM_COMMENT_START ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ TARGET_ABICALLS ; 
 int /*<<< orphan*/  TARGET_IRIX ; 
 scalar_t__ TARGET_LONG64 ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  default_file_start () ; 
 scalar_t__ flag_verbose_asm ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int mips_abi ; 
 TYPE_1__* mips_arch_info ; 
 int mips_isa ; 
 int mips_section_threshold ; 

__attribute__((used)) static void
mips_file_start (void)
{
  default_file_start ();

  if (!TARGET_IRIX)
    {
      /* Generate a special section to describe the ABI switches used to
	 produce the resultant binary.  This used to be done by the assembler
	 setting bits in the ELF header's flags field, but we have run out of
	 bits.  GDB needs this information in order to be able to correctly
	 debug these binaries.  See the function mips_gdbarch_init() in
	 gdb/mips-tdep.c.  This is unnecessary for the IRIX 5/6 ABIs and
	 causes unnecessary IRIX 6 ld warnings.  */
      const char * abi_string = NULL;

      switch (mips_abi)
	{
	case ABI_32:   abi_string = "abi32"; break;
	case ABI_N32:  abi_string = "abiN32"; break;
	case ABI_64:   abi_string = "abi64"; break;
	case ABI_O64:  abi_string = "abiO64"; break;
	case ABI_EABI: abi_string = TARGET_64BIT ? "eabi64" : "eabi32"; break;
	default:
	  gcc_unreachable ();
	}
      /* Note - we use fprintf directly rather than calling switch_to_section
	 because in this way we can avoid creating an allocated section.  We
	 do not want this section to take up any space in the running
	 executable.  */
      fprintf (asm_out_file, "\t.section .mdebug.%s\n", abi_string);

      /* There is no ELF header flag to distinguish long32 forms of the
	 EABI from long64 forms.  Emit a special section to help tools
	 such as GDB.  Do the same for o64, which is sometimes used with
	 -mlong64.  */
      if (mips_abi == ABI_EABI || mips_abi == ABI_O64)
	fprintf (asm_out_file, "\t.section .gcc_compiled_long%d\n",
		 TARGET_LONG64 ? 64 : 32);

      /* Restore the default section.  */
      fprintf (asm_out_file, "\t.previous\n");
    }

  /* Generate the pseudo ops that System V.4 wants.  */
  if (TARGET_ABICALLS)
    fprintf (asm_out_file, "\t.abicalls\n");

  if (TARGET_MIPS16)
    fprintf (asm_out_file, "\t.set\tmips16\n");

  if (flag_verbose_asm)
    fprintf (asm_out_file, "\n%s -G value = %d, Arch = %s, ISA = %d\n",
	     ASM_COMMENT_START,
	     mips_section_threshold, mips_arch_info->name, mips_isa);
}