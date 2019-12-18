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
struct gdbarch_tdep {int num_xmm_regs; int mm0_regnum; scalar_t__ gregset_reg_offset; int /*<<< orphan*/  st0_regnum; int /*<<< orphan*/  sizeof_fpregset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_EFLAGS_REGNUM ; 
 int /*<<< orphan*/  AMD64_NUM_REGS ; 
 int /*<<< orphan*/  AMD64_RIP_REGNUM ; 
 int /*<<< orphan*/  AMD64_RSP_REGNUM ; 
 int /*<<< orphan*/  AMD64_ST0_REGNUM ; 
 int /*<<< orphan*/  I387_SIZEOF_FXSAVE ; 
 int /*<<< orphan*/  amd64_convert_register_p ; 
 int /*<<< orphan*/  amd64_dwarf_reg_to_regnum ; 
 int /*<<< orphan*/  amd64_frame_align ; 
 int /*<<< orphan*/  amd64_frame_base ; 
 int /*<<< orphan*/  amd64_frame_sniffer ; 
 int /*<<< orphan*/  amd64_push_dummy_call ; 
 int /*<<< orphan*/  amd64_register_name ; 
 int /*<<< orphan*/  amd64_register_type ; 
 int /*<<< orphan*/  amd64_regset_from_core_section ; 
 int /*<<< orphan*/  amd64_return_value ; 
 int /*<<< orphan*/  amd64_sigtramp_frame_sniffer ; 
 int /*<<< orphan*/  amd64_skip_prologue ; 
 int /*<<< orphan*/  amd64_unwind_dummy_id ; 
 int /*<<< orphan*/  frame_base_set_default (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_unwind_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  i387_register_to_value ; 
 int /*<<< orphan*/  i387_value_to_register ; 
 int /*<<< orphan*/  in_plt_section ; 
 int /*<<< orphan*/  set_gdbarch_convert_register_p (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_dwarf2_reg_to_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_dwarf_reg_to_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_fp0_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_frame_align (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_frame_red_zone_size (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_in_solib_call_trampoline (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_long_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_double_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_long_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_num_pseudo_regs (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_num_regs (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pc_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_ps_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_ptr_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_push_dummy_call (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_name (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_to_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_type (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_regset_from_core_section (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_return_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_skip_prologue (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_sp_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_stab_reg_to_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_unwind_dummy_id (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_value_to_register (struct gdbarch*,int /*<<< orphan*/ ) ; 

void
amd64_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  /* AMD64 generally uses `fxsave' instead of `fsave' for saving its
     floating-point registers.  */
  tdep->sizeof_fpregset = I387_SIZEOF_FXSAVE;

  /* AMD64 has an FPU and 16 SSE registers.  */
  tdep->st0_regnum = AMD64_ST0_REGNUM;
  tdep->num_xmm_regs = 16;

  /* This is what all the fuss is about.  */
  set_gdbarch_long_bit (gdbarch, 64);
  set_gdbarch_long_long_bit (gdbarch, 64);
  set_gdbarch_ptr_bit (gdbarch, 64);

  /* In contrast to the i386, on AMD64 a `long double' actually takes
     up 128 bits, even though it's still based on the i387 extended
     floating-point format which has only 80 significant bits.  */
  set_gdbarch_long_double_bit (gdbarch, 128);

  set_gdbarch_num_regs (gdbarch, AMD64_NUM_REGS);
  set_gdbarch_register_name (gdbarch, amd64_register_name);
  set_gdbarch_register_type (gdbarch, amd64_register_type);

  /* Register numbers of various important registers.  */
  set_gdbarch_sp_regnum (gdbarch, AMD64_RSP_REGNUM); /* %rsp */
  set_gdbarch_pc_regnum (gdbarch, AMD64_RIP_REGNUM); /* %rip */
  set_gdbarch_ps_regnum (gdbarch, AMD64_EFLAGS_REGNUM); /* %eflags */
  set_gdbarch_fp0_regnum (gdbarch, AMD64_ST0_REGNUM); /* %st(0) */

  /* The "default" register numbering scheme for AMD64 is referred to
     as the "DWARF Register Number Mapping" in the System V psABI.
     The preferred debugging format for all known AMD64 targets is
     actually DWARF2, and GCC doesn't seem to support DWARF (that is
     DWARF-1), but we provide the same mapping just in case.  This
     mapping is also used for stabs, which GCC does support.  */
  set_gdbarch_stab_reg_to_regnum (gdbarch, amd64_dwarf_reg_to_regnum);
  set_gdbarch_dwarf_reg_to_regnum (gdbarch, amd64_dwarf_reg_to_regnum);
  set_gdbarch_dwarf2_reg_to_regnum (gdbarch, amd64_dwarf_reg_to_regnum);

  /* We don't override SDB_REG_RO_REGNUM, since COFF doesn't seem to
     be in use on any of the supported AMD64 targets.  */

  /* Call dummy code.  */
  set_gdbarch_push_dummy_call (gdbarch, amd64_push_dummy_call);
  set_gdbarch_frame_align (gdbarch, amd64_frame_align);
  set_gdbarch_frame_red_zone_size (gdbarch, 128);

  set_gdbarch_convert_register_p (gdbarch, amd64_convert_register_p);
  set_gdbarch_register_to_value (gdbarch, i387_register_to_value);
  set_gdbarch_value_to_register (gdbarch, i387_value_to_register);

  set_gdbarch_return_value (gdbarch, amd64_return_value);

  set_gdbarch_skip_prologue (gdbarch, amd64_skip_prologue);

  /* Avoid wiring in the MMX registers for now.  */
  set_gdbarch_num_pseudo_regs (gdbarch, 0);
  tdep->mm0_regnum = -1;

  set_gdbarch_unwind_dummy_id (gdbarch, amd64_unwind_dummy_id);

  /* FIXME: kettenis/20021026: This is ELF-specific.  Fine for now,
     since all supported AMD64 targets are ELF, but that might change
     in the future.  */
  set_gdbarch_in_solib_call_trampoline (gdbarch, in_plt_section);

  frame_unwind_append_sniffer (gdbarch, amd64_sigtramp_frame_sniffer);
  frame_unwind_append_sniffer (gdbarch, amd64_frame_sniffer);
  frame_base_set_default (gdbarch, &amd64_frame_base);

  /* If we have a register mapping, enable the generic core file support.  */
  if (tdep->gregset_reg_offset)
    set_gdbarch_regset_from_core_section (gdbarch,
					  amd64_regset_from_core_section);
}