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
struct ui_file {int dummy; } ;
struct gdbarch_tdep {int elf_flags; size_t mips_abi; int /*<<< orphan*/  default_mask_address_p; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int A0_REGNUM ; 
 int /*<<< orphan*/  ADDR ; 
 int /*<<< orphan*/  ADDR_BITS_REMOVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARGS ; 
 int /*<<< orphan*/  ATTACH_DETACH ; 
 int /*<<< orphan*/  BP_P ; 
 int /*<<< orphan*/  CNT ; 
 int /*<<< orphan*/  DWARF_REG_TO_REGNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECOFF_REG_TO_REGNUM (int /*<<< orphan*/ ) ; 
 int EF_MIPS_32BITMODE ; 
 int EF_MIPS_ARCH ; 
#define  E_MIPS_ARCH_1 131 
#define  E_MIPS_ARCH_2 130 
#define  E_MIPS_ARCH_3 129 
#define  E_MIPS_ARCH_4 128 
 long FIRST_EMBED_REGNUM ; 
 long FP_REGISTER_DOUBLE ; 
 int /*<<< orphan*/  IGNORE_HELPER_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_SOLIB_CALL_TRAMPOLINE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_SOLIB_RETURN_TRAMPOLINE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long LAST_EMBED_REGNUM ; 
 long MACHINE_CPROC_FP_OFFSET ; 
 long MACHINE_CPROC_PC_OFFSET ; 
 long MACHINE_CPROC_SP_OFFSET ; 
 long MIPS16_INSTLEN ; 
 int /*<<< orphan*/  MIPS_DEFAULT_FPU_TYPE ; 
 long MIPS_EABI ; 
 int /*<<< orphan*/  MIPS_FPU_DOUBLE ; 
 int /*<<< orphan*/  MIPS_FPU_NONE ; 
 int /*<<< orphan*/  MIPS_FPU_SINGLE ; 
 int /*<<< orphan*/  MIPS_FPU_TYPE ; 
 long MIPS_INSTLEN ; 
 int MIPS_LAST_ARG_REGNUM ; 
 long MIPS_NUMREGS ; 
 int /*<<< orphan*/  NAME ; 
 int /*<<< orphan*/  NUMARGS ; 
 int /*<<< orphan*/  OTHERTYPE ; 
 int /*<<< orphan*/  PC ; 
 long PRID_REGNUM ; 
 long PS_REGNUM ; 
 long RA_REGNUM ; 
 int /*<<< orphan*/  REGNUM ; 
 long SAVED_BYTES ; 
 long SAVED_FP ; 
 long SAVED_PC ; 
 int /*<<< orphan*/  SETUP_ARBITRARY_FRAME (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG ; 
 int /*<<< orphan*/  SKIP_TRAMPOLINE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFTWARE_SINGLE_STEP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long SOFTWARE_SINGLE_STEP_P () ; 
 int /*<<< orphan*/  STAB_REG_TO_REGNUM (int /*<<< orphan*/ ) ; 
 long STACK_END_ADDR ; 
 int /*<<< orphan*/  STATE ; 
 int /*<<< orphan*/  STEP_SKIPS_DELAY (int /*<<< orphan*/ ) ; 
 long STEP_SKIPS_DELAY_P ; 
 int /*<<< orphan*/  STOPPED_BY_WATCHPOINT (int /*<<< orphan*/ ) ; 
 long T9_REGNUM ; 
 int /*<<< orphan*/  TARGET_CAN_USE_HARDWARE_WATCHPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_HAS_HARDWARE_WATCHPOINTS ; 
 int /*<<< orphan*/  THREAD ; 
 int /*<<< orphan*/  TRACE_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long TRACE_FLAVOR ; 
 long TRACE_FLAVOR_SIZE ; 
 int /*<<< orphan*/  TRACE_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE ; 
 long UNUSED_REGNUM ; 
 long V0_REGNUM ; 
 scalar_t__ VM_MIN_ADDRESS ; 
 int /*<<< orphan*/  WS ; 
 int /*<<< orphan*/  X ; 
 long XSTRING (int /*<<< orphan*/ ) ; 
 long ZERO_REGNUM ; 
 long _PROC_MAGIC_ ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/ * mips_abi_strings ; 
 int /*<<< orphan*/  mips_mask_address_p (struct gdbarch_tdep*) ; 
 long mips_saved_regsize (struct gdbarch_tdep*) ; 
 long mips_stack_argsize (struct gdbarch_tdep*) ; 

__attribute__((used)) static void
mips_dump_tdep (struct gdbarch *current_gdbarch, struct ui_file *file)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  if (tdep != NULL)
    {
      int ef_mips_arch;
      int ef_mips_32bitmode;
      /* determine the ISA */
      switch (tdep->elf_flags & EF_MIPS_ARCH)
	{
	case E_MIPS_ARCH_1:
	  ef_mips_arch = 1;
	  break;
	case E_MIPS_ARCH_2:
	  ef_mips_arch = 2;
	  break;
	case E_MIPS_ARCH_3:
	  ef_mips_arch = 3;
	  break;
	case E_MIPS_ARCH_4:
	  ef_mips_arch = 4;
	  break;
	default:
	  ef_mips_arch = 0;
	  break;
	}
      /* determine the size of a pointer */
      ef_mips_32bitmode = (tdep->elf_flags & EF_MIPS_32BITMODE);
      fprintf_unfiltered (file,
			  "mips_dump_tdep: tdep->elf_flags = 0x%x\n",
			  tdep->elf_flags);
      fprintf_unfiltered (file,
			  "mips_dump_tdep: ef_mips_32bitmode = %d\n",
			  ef_mips_32bitmode);
      fprintf_unfiltered (file,
			  "mips_dump_tdep: ef_mips_arch = %d\n",
			  ef_mips_arch);
      fprintf_unfiltered (file,
			  "mips_dump_tdep: tdep->mips_abi = %d (%s)\n",
			  tdep->mips_abi, mips_abi_strings[tdep->mips_abi]);
      fprintf_unfiltered (file,
			  "mips_dump_tdep: mips_mask_address_p() %d (default %d)\n",
			  mips_mask_address_p (tdep),
			  tdep->default_mask_address_p);
    }
  fprintf_unfiltered (file,
		      "mips_dump_tdep: FP_REGISTER_DOUBLE = %d\n",
		      FP_REGISTER_DOUBLE);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS_DEFAULT_FPU_TYPE = %d (%s)\n",
		      MIPS_DEFAULT_FPU_TYPE,
		      (MIPS_DEFAULT_FPU_TYPE == MIPS_FPU_NONE ? "none"
		       : MIPS_DEFAULT_FPU_TYPE == MIPS_FPU_SINGLE ? "single"
		       : MIPS_DEFAULT_FPU_TYPE == MIPS_FPU_DOUBLE ? "double"
		       : "???"));
  fprintf_unfiltered (file, "mips_dump_tdep: MIPS_EABI = %d\n", MIPS_EABI);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS_FPU_TYPE = %d (%s)\n",
		      MIPS_FPU_TYPE,
		      (MIPS_FPU_TYPE == MIPS_FPU_NONE ? "none"
		       : MIPS_FPU_TYPE == MIPS_FPU_SINGLE ? "single"
		       : MIPS_FPU_TYPE == MIPS_FPU_DOUBLE ? "double"
		       : "???"));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: FP_REGISTER_DOUBLE = %d\n",
		      FP_REGISTER_DOUBLE);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: mips_stack_argsize() = %d\n",
		      mips_stack_argsize (tdep));
  fprintf_unfiltered (file, "mips_dump_tdep: A0_REGNUM = %d\n", A0_REGNUM);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: ADDR_BITS_REMOVE # %s\n",
		      XSTRING (ADDR_BITS_REMOVE (ADDR)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: ATTACH_DETACH # %s\n",
		      XSTRING (ATTACH_DETACH));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: DWARF_REG_TO_REGNUM # %s\n",
		      XSTRING (DWARF_REG_TO_REGNUM (REGNUM)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: ECOFF_REG_TO_REGNUM # %s\n",
		      XSTRING (ECOFF_REG_TO_REGNUM (REGNUM)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: FIRST_EMBED_REGNUM = %d\n",
		      FIRST_EMBED_REGNUM);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: IGNORE_HELPER_CALL # %s\n",
		      XSTRING (IGNORE_HELPER_CALL (PC)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: IN_SOLIB_CALL_TRAMPOLINE # %s\n",
		      XSTRING (IN_SOLIB_CALL_TRAMPOLINE (PC, NAME)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: IN_SOLIB_RETURN_TRAMPOLINE # %s\n",
		      XSTRING (IN_SOLIB_RETURN_TRAMPOLINE (PC, NAME)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: LAST_EMBED_REGNUM = %d\n",
		      LAST_EMBED_REGNUM);
#ifdef MACHINE_CPROC_FP_OFFSET
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MACHINE_CPROC_FP_OFFSET = %d\n",
		      MACHINE_CPROC_FP_OFFSET);
#endif
#ifdef MACHINE_CPROC_PC_OFFSET
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MACHINE_CPROC_PC_OFFSET = %d\n",
		      MACHINE_CPROC_PC_OFFSET);
#endif
#ifdef MACHINE_CPROC_SP_OFFSET
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MACHINE_CPROC_SP_OFFSET = %d\n",
		      MACHINE_CPROC_SP_OFFSET);
#endif
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS16_INSTLEN = %d\n",
		      MIPS16_INSTLEN);
  fprintf_unfiltered (file, "mips_dump_tdep: MIPS_DEFAULT_ABI = FIXME!\n");
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS_EFI_SYMBOL_NAME = multi-arch!!\n");
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS_INSTLEN = %d\n", MIPS_INSTLEN);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS_LAST_ARG_REGNUM = %d (%d regs)\n",
		      MIPS_LAST_ARG_REGNUM,
		      MIPS_LAST_ARG_REGNUM - A0_REGNUM + 1);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: MIPS_NUMREGS = %d\n", MIPS_NUMREGS);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: mips_saved_regsize() = %d\n",
		      mips_saved_regsize (tdep));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: PRID_REGNUM = %d\n", PRID_REGNUM);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: PROC_DESC_IS_DUMMY = function?\n");
  fprintf_unfiltered (file,
		      "mips_dump_tdep: PROC_FRAME_ADJUST = function?\n");
  fprintf_unfiltered (file,
		      "mips_dump_tdep: PROC_FRAME_OFFSET = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_FRAME_REG = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_FREG_MASK = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_FREG_OFFSET = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_HIGH_ADDR = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_LOW_ADDR = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_PC_REG = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_REG_MASK = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_REG_OFFSET = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PROC_SYMBOL = function?\n");
  fprintf_unfiltered (file, "mips_dump_tdep: PS_REGNUM = %d\n", PS_REGNUM);
  fprintf_unfiltered (file, "mips_dump_tdep: RA_REGNUM = %d\n", RA_REGNUM);
#ifdef SAVED_BYTES
  fprintf_unfiltered (file,
		      "mips_dump_tdep: SAVED_BYTES = %d\n", SAVED_BYTES);
#endif
#ifdef SAVED_FP
  fprintf_unfiltered (file, "mips_dump_tdep: SAVED_FP = %d\n", SAVED_FP);
#endif
#ifdef SAVED_PC
  fprintf_unfiltered (file, "mips_dump_tdep: SAVED_PC = %d\n", SAVED_PC);
#endif
  fprintf_unfiltered (file,
		      "mips_dump_tdep: SETUP_ARBITRARY_FRAME # %s\n",
		      XSTRING (SETUP_ARBITRARY_FRAME (NUMARGS, ARGS)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: SET_PROC_DESC_IS_DUMMY = function?\n");
  fprintf_unfiltered (file,
		      "mips_dump_tdep: SKIP_TRAMPOLINE_CODE # %s\n",
		      XSTRING (SKIP_TRAMPOLINE_CODE (PC)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: SOFTWARE_SINGLE_STEP # %s\n",
		      XSTRING (SOFTWARE_SINGLE_STEP (SIG, BP_P)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: SOFTWARE_SINGLE_STEP_P () = %d\n",
		      SOFTWARE_SINGLE_STEP_P ());
  fprintf_unfiltered (file,
		      "mips_dump_tdep: STAB_REG_TO_REGNUM # %s\n",
		      XSTRING (STAB_REG_TO_REGNUM (REGNUM)));
#ifdef STACK_END_ADDR
  fprintf_unfiltered (file,
		      "mips_dump_tdep: STACK_END_ADDR = %d\n",
		      STACK_END_ADDR);
#endif
  fprintf_unfiltered (file,
		      "mips_dump_tdep: STEP_SKIPS_DELAY # %s\n",
		      XSTRING (STEP_SKIPS_DELAY (PC)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: STEP_SKIPS_DELAY_P = %d\n",
		      STEP_SKIPS_DELAY_P);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: STOPPED_BY_WATCHPOINT # %s\n",
		      XSTRING (STOPPED_BY_WATCHPOINT (WS)));
  fprintf_unfiltered (file, "mips_dump_tdep: T9_REGNUM = %d\n", T9_REGNUM);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TABULAR_REGISTER_OUTPUT = used?\n");
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TARGET_CAN_USE_HARDWARE_WATCHPOINT # %s\n",
		      XSTRING (TARGET_CAN_USE_HARDWARE_WATCHPOINT
			       (TYPE, CNT, OTHERTYPE)));
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TARGET_HAS_HARDWARE_WATCHPOINTS # %s\n",
		      XSTRING (TARGET_HAS_HARDWARE_WATCHPOINTS));
#ifdef TRACE_CLEAR
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TRACE_CLEAR # %s\n",
		      XSTRING (TRACE_CLEAR (THREAD, STATE)));
#endif
#ifdef TRACE_FLAVOR
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TRACE_FLAVOR = %d\n", TRACE_FLAVOR);
#endif
#ifdef TRACE_FLAVOR_SIZE
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TRACE_FLAVOR_SIZE = %d\n",
		      TRACE_FLAVOR_SIZE);
#endif
#ifdef TRACE_SET
  fprintf_unfiltered (file,
		      "mips_dump_tdep: TRACE_SET # %s\n",
		      XSTRING (TRACE_SET (X, STATE)));
#endif
#ifdef UNUSED_REGNUM
  fprintf_unfiltered (file,
		      "mips_dump_tdep: UNUSED_REGNUM = %d\n", UNUSED_REGNUM);
#endif
  fprintf_unfiltered (file, "mips_dump_tdep: V0_REGNUM = %d\n", V0_REGNUM);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: VM_MIN_ADDRESS = %ld\n",
		      (long) VM_MIN_ADDRESS);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: ZERO_REGNUM = %d\n", ZERO_REGNUM);
  fprintf_unfiltered (file,
		      "mips_dump_tdep: _PROC_MAGIC_ = %d\n", _PROC_MAGIC_);
}