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
struct gdbarch_tdep {int sc_pc_offset; int sc_regs_offset; int sc_fpregs_offset; int jb_pc; int /*<<< orphan*/ * sigcontext_addr; int /*<<< orphan*/ * dynamic_sigtramp_offset; scalar_t__ vm_min_address; } ;
struct gdbarch_list {struct gdbarch* gdbarch; } ;
struct gdbarch_info {scalar_t__ osabi; int /*<<< orphan*/ * abfd; } ;
struct gdbarch {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_FP0_REGNUM ; 
 int /*<<< orphan*/  ALPHA_NUM_REGS ; 
 int /*<<< orphan*/  ALPHA_PC_REGNUM ; 
 int /*<<< orphan*/  ALPHA_SP_REGNUM ; 
 scalar_t__ GDB_OSABI_OSF1 ; 
 scalar_t__ GDB_OSABI_UNKNOWN ; 
 int /*<<< orphan*/  alpha_breakpoint_from_pc ; 
 int /*<<< orphan*/  alpha_cannot_fetch_register ; 
 int /*<<< orphan*/  alpha_cannot_store_register ; 
 int /*<<< orphan*/  alpha_convert_register_p ; 
 int /*<<< orphan*/  alpha_extract_return_value ; 
 int /*<<< orphan*/  alpha_extract_struct_value_address ; 
 int /*<<< orphan*/  alpha_get_longjmp_target ; 
 int /*<<< orphan*/  alpha_heuristic_frame_base ; 
 int /*<<< orphan*/  alpha_heuristic_frame_sniffer ; 
 int /*<<< orphan*/  alpha_push_dummy_call ; 
 int /*<<< orphan*/  alpha_register_byte ; 
 int /*<<< orphan*/  alpha_register_name ; 
 int /*<<< orphan*/  alpha_register_raw_size ; 
 int /*<<< orphan*/  alpha_register_reggroup_p ; 
 int /*<<< orphan*/  alpha_register_to_value ; 
 int /*<<< orphan*/  alpha_register_type ; 
 int /*<<< orphan*/  alpha_register_virtual_size ; 
 int /*<<< orphan*/  alpha_sigtramp_frame_sniffer ; 
 int /*<<< orphan*/  alpha_skip_prologue ; 
 int /*<<< orphan*/  alpha_store_return_value ; 
 int /*<<< orphan*/  alpha_unwind_dummy_id ; 
 int /*<<< orphan*/  alpha_unwind_pc ; 
 int /*<<< orphan*/  alpha_value_to_register ; 
 int /*<<< orphan*/  always_use_struct_convention ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_ecoff_flavour ; 
 int /*<<< orphan*/  core_addr_lessthan ; 
 int /*<<< orphan*/  find_solib_trampoline_target ; 
 int /*<<< orphan*/  frame_base_set_default (struct gdbarch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_unwind_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 
 struct gdbarch* gdbarch_alloc (struct gdbarch_info*,struct gdbarch_tdep*) ; 
 int /*<<< orphan*/  gdbarch_init_osabi (struct gdbarch_info,struct gdbarch*) ; 
 struct gdbarch_list* gdbarch_list_lookup_by_info (struct gdbarch_list*,struct gdbarch_info*) ; 
 int /*<<< orphan*/  print_insn_alpha ; 
 int /*<<< orphan*/  set_gdbarch_breakpoint_from_pc (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_cannot_fetch_register (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_cannot_store_register (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_convert_register_p (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_decr_pc_after_break (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_deprecated_extract_struct_value_address (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_deprecated_register_byte (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_deprecated_register_raw_size (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_deprecated_register_virtual_size (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_double_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_extract_return_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_float_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_fp0_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_get_longjmp_target (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_inner_than (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_int_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_double_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_long_long_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_num_regs (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_pc_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_print_insn (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_ptr_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_push_dummy_call (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_name (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_reggroup_p (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_to_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_register_type (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_short_bit (struct gdbarch*,int) ; 
 int /*<<< orphan*/  set_gdbarch_skip_prologue (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_skip_trampoline_code (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_sp_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_store_return_value (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_unwind_dummy_id (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_unwind_pc (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_use_struct_convention (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_value_to_register (struct gdbarch*,int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* xmalloc (int) ; 

__attribute__((used)) static struct gdbarch *
alpha_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
  struct gdbarch_tdep *tdep;
  struct gdbarch *gdbarch;

  /* Try to determine the ABI of the object we are loading.  */
  if (info.abfd != NULL && info.osabi == GDB_OSABI_UNKNOWN)
    {
      /* If it's an ECOFF file, assume it's OSF/1.  */
      if (bfd_get_flavour (info.abfd) == bfd_target_ecoff_flavour)
	info.osabi = GDB_OSABI_OSF1;
    }

  /* Find a candidate among extant architectures.  */
  arches = gdbarch_list_lookup_by_info (arches, &info);
  if (arches != NULL)
    return arches->gdbarch;

  tdep = xmalloc (sizeof (struct gdbarch_tdep));
  gdbarch = gdbarch_alloc (&info, tdep);

  /* Lowest text address.  This is used by heuristic_proc_start()
     to decide when to stop looking.  */
  tdep->vm_min_address = (CORE_ADDR) 0x120000000;

  tdep->dynamic_sigtramp_offset = NULL;
  tdep->sigcontext_addr = NULL;
  tdep->sc_pc_offset = 2 * 8;
  tdep->sc_regs_offset = 4 * 8;
  tdep->sc_fpregs_offset = tdep->sc_regs_offset + 32 * 8 + 8;

  tdep->jb_pc = -1;	/* longjmp support not enabled by default  */

  /* Type sizes */
  set_gdbarch_short_bit (gdbarch, 16);
  set_gdbarch_int_bit (gdbarch, 32);
  set_gdbarch_long_bit (gdbarch, 64);
  set_gdbarch_long_long_bit (gdbarch, 64);
  set_gdbarch_float_bit (gdbarch, 32);
  set_gdbarch_double_bit (gdbarch, 64);
  set_gdbarch_long_double_bit (gdbarch, 64);
  set_gdbarch_ptr_bit (gdbarch, 64);

  /* Register info */
  set_gdbarch_num_regs (gdbarch, ALPHA_NUM_REGS);
  set_gdbarch_sp_regnum (gdbarch, ALPHA_SP_REGNUM);
  set_gdbarch_pc_regnum (gdbarch, ALPHA_PC_REGNUM);
  set_gdbarch_fp0_regnum (gdbarch, ALPHA_FP0_REGNUM);

  set_gdbarch_register_name (gdbarch, alpha_register_name);
  set_gdbarch_deprecated_register_byte (gdbarch, alpha_register_byte);
  set_gdbarch_deprecated_register_raw_size (gdbarch, alpha_register_raw_size);
  set_gdbarch_deprecated_register_virtual_size (gdbarch, alpha_register_virtual_size);
  set_gdbarch_register_type (gdbarch, alpha_register_type);

  set_gdbarch_cannot_fetch_register (gdbarch, alpha_cannot_fetch_register);
  set_gdbarch_cannot_store_register (gdbarch, alpha_cannot_store_register);

  set_gdbarch_convert_register_p (gdbarch, alpha_convert_register_p);
  set_gdbarch_register_to_value (gdbarch, alpha_register_to_value);
  set_gdbarch_value_to_register (gdbarch, alpha_value_to_register);

  set_gdbarch_register_reggroup_p (gdbarch, alpha_register_reggroup_p);

  /* Prologue heuristics.  */
  set_gdbarch_skip_prologue (gdbarch, alpha_skip_prologue);

  /* Disassembler.  */
  set_gdbarch_print_insn (gdbarch, print_insn_alpha);

  /* Call info.  */

  set_gdbarch_use_struct_convention (gdbarch, always_use_struct_convention);
  set_gdbarch_extract_return_value (gdbarch, alpha_extract_return_value);
  set_gdbarch_store_return_value (gdbarch, alpha_store_return_value);
  set_gdbarch_deprecated_extract_struct_value_address (gdbarch, alpha_extract_struct_value_address);

  /* Settings for calling functions in the inferior.  */
  set_gdbarch_push_dummy_call (gdbarch, alpha_push_dummy_call);

  /* Methods for saving / extracting a dummy frame's ID.  */
  set_gdbarch_unwind_dummy_id (gdbarch, alpha_unwind_dummy_id);

  /* Return the unwound PC value.  */
  set_gdbarch_unwind_pc (gdbarch, alpha_unwind_pc);

  set_gdbarch_inner_than (gdbarch, core_addr_lessthan);
  set_gdbarch_skip_trampoline_code (gdbarch, find_solib_trampoline_target);

  set_gdbarch_breakpoint_from_pc (gdbarch, alpha_breakpoint_from_pc);
  set_gdbarch_decr_pc_after_break (gdbarch, 4);

  /* Hook in ABI-specific overrides, if they have been registered.  */
  gdbarch_init_osabi (info, gdbarch);

  /* Now that we have tuned the configuration, set a few final things
     based on what the OS ABI has told us.  */

  if (tdep->jb_pc >= 0)
    set_gdbarch_get_longjmp_target (gdbarch, alpha_get_longjmp_target);

  frame_unwind_append_sniffer (gdbarch, alpha_sigtramp_frame_sniffer);
  frame_unwind_append_sniffer (gdbarch, alpha_heuristic_frame_sniffer);

  frame_base_set_default (gdbarch, &alpha_heuristic_frame_base);

  return gdbarch;
}