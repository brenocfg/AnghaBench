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
struct mips_cpu_info {scalar_t__ isa; int flags; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ isa; int ase_mips3d; int ase_mdmx; int mips16; int ase_smartmips; int ase_dsp; int ase_dspr2; int ase_mt; int gp32; int fp32; } ;

/* Variables and functions */
 scalar_t__ ABI_NEEDS_32BIT_REGS (scalar_t__) ; 
 scalar_t__ ABI_NEEDS_64BIT_REGS (scalar_t__) ; 
 scalar_t__ CPU_HAS_MIPS16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISA_HAS_64BIT_FPRS (scalar_t__) ; 
 scalar_t__ ISA_HAS_64BIT_REGS (scalar_t__) ; 
 int /*<<< orphan*/  ISA_HAS_MXHC1 (scalar_t__) ; 
 scalar_t__ ISA_MIPS1 ; 
 int /*<<< orphan*/  ISA_SUPPORTS_DSPR2_ASE ; 
 int /*<<< orphan*/  ISA_SUPPORTS_DSP_ASE ; 
 int /*<<< orphan*/  ISA_SUPPORTS_MT_ASE ; 
 int /*<<< orphan*/  ISA_SUPPORTS_SMARTMIPS ; 
 scalar_t__ ISA_UNKNOWN ; 
 int MIPS_CPU_ASE_DSP ; 
 int MIPS_CPU_ASE_DSPR2 ; 
 int MIPS_CPU_ASE_MDMX ; 
 int MIPS_CPU_ASE_MIPS3D ; 
 int MIPS_CPU_ASE_MT ; 
 int MIPS_CPU_ASE_SMARTMIPS ; 
 scalar_t__ MIPS_CPU_STRING_DEFAULT ; 
 scalar_t__ MIPS_DEFAULT_ABI ; 
 scalar_t__ NO_ABI ; 
 scalar_t__ O32_ABI ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 int /*<<< orphan*/  TARGET_OS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (char*,...) ; 
 int /*<<< orphan*/  as_warn (char*,...) ; 
 scalar_t__ bfd_target_ecoff_flavour ; 
 int file_ase_dsp ; 
 int file_ase_dspr2 ; 
 int file_ase_mdmx ; 
 int file_ase_mips16 ; 
 int file_ase_mips3d ; 
 int file_ase_mt ; 
 int file_ase_smartmips ; 
 int /*<<< orphan*/  file_mips_arch ; 
 int file_mips_fp32 ; 
 int file_mips_gp32 ; 
 scalar_t__ file_mips_isa ; 
 scalar_t__ g_switch_seen ; 
 scalar_t__ g_switch_value ; 
 int mips_32bitmode ; 
 scalar_t__ mips_abi ; 
 scalar_t__ mips_arch_string ; 
 struct mips_cpu_info* mips_cpu_info_from_isa (scalar_t__) ; 
 int mips_flag_mdebug ; 
 TYPE_1__ mips_opts ; 
 struct mips_cpu_info* mips_parse_cpu (char*,scalar_t__) ; 
 int /*<<< orphan*/  mips_set_architecture (struct mips_cpu_info const*) ; 
 int /*<<< orphan*/  mips_set_tune (struct mips_cpu_info const*) ; 
 scalar_t__ mips_trap ; 
 scalar_t__ mips_tune_string ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void
mips_after_parse_args (void)
{
  const struct mips_cpu_info *arch_info = 0;
  const struct mips_cpu_info *tune_info = 0;

  /* GP relative stuff not working for PE */
  if (strncmp (TARGET_OS, "pe", 2) == 0)
    {
      if (g_switch_seen && g_switch_value != 0)
	as_bad (_("-G not supported in this configuration."));
      g_switch_value = 0;
    }

  if (mips_abi == NO_ABI)
    mips_abi = MIPS_DEFAULT_ABI;

  /* The following code determines the architecture and register size.
     Similar code was added to GCC 3.3 (see override_options() in
     config/mips/mips.c).  The GAS and GCC code should be kept in sync
     as much as possible.  */

  if (mips_arch_string != 0)
    arch_info = mips_parse_cpu ("-march", mips_arch_string);

  if (file_mips_isa != ISA_UNKNOWN)
    {
      /* Handle -mipsN.  At this point, file_mips_isa contains the
	 ISA level specified by -mipsN, while arch_info->isa contains
	 the -march selection (if any).  */
      if (arch_info != 0)
	{
	  /* -march takes precedence over -mipsN, since it is more descriptive.
	     There's no harm in specifying both as long as the ISA levels
	     are the same.  */
	  if (file_mips_isa != arch_info->isa)
	    as_bad (_("-%s conflicts with the other architecture options, which imply -%s"),
		    mips_cpu_info_from_isa (file_mips_isa)->name,
		    mips_cpu_info_from_isa (arch_info->isa)->name);
	}
      else
	arch_info = mips_cpu_info_from_isa (file_mips_isa);
    }

  if (arch_info == 0)
    arch_info = mips_parse_cpu ("default CPU", MIPS_CPU_STRING_DEFAULT);

  if (ABI_NEEDS_64BIT_REGS (mips_abi) && !ISA_HAS_64BIT_REGS (arch_info->isa))
    as_bad ("-march=%s is not compatible with the selected ABI",
	    arch_info->name);

  mips_set_architecture (arch_info);

  /* Optimize for file_mips_arch, unless -mtune selects a different processor.  */
  if (mips_tune_string != 0)
    tune_info = mips_parse_cpu ("-mtune", mips_tune_string);

  if (tune_info == 0)
    mips_set_tune (arch_info);
  else
    mips_set_tune (tune_info);

  if (file_mips_gp32 >= 0)
    {
      /* The user specified the size of the integer registers.  Make sure
	 it agrees with the ABI and ISA.  */
      if (file_mips_gp32 == 0 && !ISA_HAS_64BIT_REGS (mips_opts.isa))
	as_bad (_("-mgp64 used with a 32-bit processor"));
      else if (file_mips_gp32 == 1 && ABI_NEEDS_64BIT_REGS (mips_abi))
	as_bad (_("-mgp32 used with a 64-bit ABI"));
      else if (file_mips_gp32 == 0 && ABI_NEEDS_32BIT_REGS (mips_abi))
	as_bad (_("-mgp64 used with a 32-bit ABI"));
    }
  else
    {
      /* Infer the integer register size from the ABI and processor.
	 Restrict ourselves to 32-bit registers if that's all the
	 processor has, or if the ABI cannot handle 64-bit registers.  */
      file_mips_gp32 = (ABI_NEEDS_32BIT_REGS (mips_abi)
			|| !ISA_HAS_64BIT_REGS (mips_opts.isa));
    }

  switch (file_mips_fp32)
    {
    default:
    case -1:
      /* No user specified float register size.
	 ??? GAS treats single-float processors as though they had 64-bit
	 float registers (although it complains when double-precision
	 instructions are used).  As things stand, saying they have 32-bit
	 registers would lead to spurious "register must be even" messages.
	 So here we assume float registers are never smaller than the
	 integer ones.  */
      if (file_mips_gp32 == 0)
	/* 64-bit integer registers implies 64-bit float registers.  */
	file_mips_fp32 = 0;
      else if ((mips_opts.ase_mips3d > 0 || mips_opts.ase_mdmx > 0)
	       && ISA_HAS_64BIT_FPRS (mips_opts.isa))
	/* -mips3d and -mdmx imply 64-bit float registers, if possible.  */
	file_mips_fp32 = 0;
      else
	/* 32-bit float registers.  */
	file_mips_fp32 = 1;
      break;

    /* The user specified the size of the float registers.  Check if it
       agrees with the ABI and ISA.  */
    case 0:
      if (!ISA_HAS_64BIT_FPRS (mips_opts.isa))
	as_bad (_("-mfp64 used with a 32-bit fpu"));
      else if (ABI_NEEDS_32BIT_REGS (mips_abi)
	       && !ISA_HAS_MXHC1 (mips_opts.isa))
	as_warn (_("-mfp64 used with a 32-bit ABI"));
      break;
    case 1:
      if (ABI_NEEDS_64BIT_REGS (mips_abi))
	as_warn (_("-mfp32 used with a 64-bit ABI"));
      break;
    }

  /* End of GCC-shared inference code.  */

  /* This flag is set when we have a 64-bit capable CPU but use only
     32-bit wide registers.  Note that EABI does not use it.  */
  if (ISA_HAS_64BIT_REGS (mips_opts.isa)
      && ((mips_abi == NO_ABI && file_mips_gp32 == 1)
	  || mips_abi == O32_ABI))
    mips_32bitmode = 1;

  if (mips_opts.isa == ISA_MIPS1 && mips_trap)
    as_bad (_("trap exception not supported at ISA 1"));

  /* If the selected architecture includes support for ASEs, enable
     generation of code for them.  */
  if (mips_opts.mips16 == -1)
    mips_opts.mips16 = (CPU_HAS_MIPS16 (file_mips_arch)) ? 1 : 0;
  if (mips_opts.ase_mips3d == -1)
    mips_opts.ase_mips3d = ((arch_info->flags & MIPS_CPU_ASE_MIPS3D)
			    && file_mips_fp32 == 0) ? 1 : 0;
  if (mips_opts.ase_mips3d && file_mips_fp32 == 1)
    as_bad (_("-mfp32 used with -mips3d"));

  if (mips_opts.ase_mdmx == -1)
    mips_opts.ase_mdmx = ((arch_info->flags & MIPS_CPU_ASE_MDMX)
			  && file_mips_fp32 == 0) ? 1 : 0;
  if (mips_opts.ase_mdmx && file_mips_fp32 == 1)
    as_bad (_("-mfp32 used with -mdmx"));

  if (mips_opts.ase_smartmips == -1)
    mips_opts.ase_smartmips = (arch_info->flags & MIPS_CPU_ASE_SMARTMIPS) ? 1 : 0;
  if (mips_opts.ase_smartmips && !ISA_SUPPORTS_SMARTMIPS)
      as_warn ("%s ISA does not support SmartMIPS", 
	       mips_cpu_info_from_isa (mips_opts.isa)->name);

  if (mips_opts.ase_dsp == -1)
    mips_opts.ase_dsp = (arch_info->flags & MIPS_CPU_ASE_DSP) ? 1 : 0;
  if (mips_opts.ase_dsp && !ISA_SUPPORTS_DSP_ASE)
      as_warn ("%s ISA does not support DSP ASE", 
	       mips_cpu_info_from_isa (mips_opts.isa)->name);

  if (mips_opts.ase_dspr2 == -1)
    {
      mips_opts.ase_dspr2 = (arch_info->flags & MIPS_CPU_ASE_DSPR2) ? 1 : 0;
      mips_opts.ase_dsp = (arch_info->flags & MIPS_CPU_ASE_DSP) ? 1 : 0;
    }
  if (mips_opts.ase_dspr2 && !ISA_SUPPORTS_DSPR2_ASE)
      as_warn ("%s ISA does not support DSP R2 ASE",
	       mips_cpu_info_from_isa (mips_opts.isa)->name);

  if (mips_opts.ase_mt == -1)
    mips_opts.ase_mt = (arch_info->flags & MIPS_CPU_ASE_MT) ? 1 : 0;
  if (mips_opts.ase_mt && !ISA_SUPPORTS_MT_ASE)
      as_warn ("%s ISA does not support MT ASE",
	       mips_cpu_info_from_isa (mips_opts.isa)->name);

  file_mips_isa = mips_opts.isa;
  file_ase_mips16 = mips_opts.mips16;
  file_ase_mips3d = mips_opts.ase_mips3d;
  file_ase_mdmx = mips_opts.ase_mdmx;
  file_ase_smartmips = mips_opts.ase_smartmips;
  file_ase_dsp = mips_opts.ase_dsp;
  file_ase_dspr2 = mips_opts.ase_dspr2;
  file_ase_mt = mips_opts.ase_mt;
  mips_opts.gp32 = file_mips_gp32;
  mips_opts.fp32 = file_mips_fp32;

  if (mips_flag_mdebug < 0)
    {
#ifdef OBJ_MAYBE_ECOFF
      if (OUTPUT_FLAVOR == bfd_target_ecoff_flavour)
	mips_flag_mdebug = 1;
      else
#endif /* OBJ_MAYBE_ECOFF */
	mips_flag_mdebug = 0;
    }
}