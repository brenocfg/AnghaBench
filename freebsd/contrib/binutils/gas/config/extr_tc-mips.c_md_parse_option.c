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
struct TYPE_2__ {int ase_mdmx; int ase_dsp; int ase_dspr2; int ase_mt; int mips16; int ase_mips3d; int ase_smartmips; void* sym32; } ;

/* Variables and functions */
 int /*<<< orphan*/  EABI_ABI ; 
 void* FALSE ; 
 int /*<<< orphan*/  ISA_MIPS1 ; 
 int /*<<< orphan*/  ISA_MIPS2 ; 
 int /*<<< orphan*/  ISA_MIPS3 ; 
 int /*<<< orphan*/  ISA_MIPS32 ; 
 int /*<<< orphan*/  ISA_MIPS32R2 ; 
 int /*<<< orphan*/  ISA_MIPS4 ; 
 int /*<<< orphan*/  ISA_MIPS5 ; 
 int /*<<< orphan*/  ISA_MIPS64 ; 
 int /*<<< orphan*/  ISA_MIPS64R2 ; 
 int /*<<< orphan*/  IS_ELF ; 
 int /*<<< orphan*/  N32_ABI ; 
 int /*<<< orphan*/  N64_ABI ; 
 int /*<<< orphan*/  NO_PIC ; 
 int /*<<< orphan*/  O32_ABI ; 
 int /*<<< orphan*/  O64_ABI ; 
#define  OPTION_32 198 
#define  OPTION_64 197 
#define  OPTION_BREAK 196 
#define  OPTION_CALL_SHARED 195 
#define  OPTION_CONSTRUCT_FLOATS 194 
#define  OPTION_DSP 193 
#define  OPTION_DSPR2 192 
#define  OPTION_EB 191 
#define  OPTION_EL 190 
#define  OPTION_FIX_VR4120 189 
#define  OPTION_FIX_VR4130 188 
#define  OPTION_FP32 187 
#define  OPTION_FP64 186 
#define  OPTION_GP32 185 
#define  OPTION_GP64 184 
#define  OPTION_M3900 183 
#define  OPTION_M4010 182 
#define  OPTION_M4100 181 
#define  OPTION_M4650 180 
#define  OPTION_M7000_HILO_FIX 179 
#define  OPTION_MABI 178 
#define  OPTION_MARCH 177 
#define  OPTION_MDEBUG 176 
#define  OPTION_MDMX 175 
#define  OPTION_MIPS1 174 
#define  OPTION_MIPS16 173 
#define  OPTION_MIPS2 172 
#define  OPTION_MIPS3 171 
#define  OPTION_MIPS32 170 
#define  OPTION_MIPS32R2 169 
#define  OPTION_MIPS3D 168 
#define  OPTION_MIPS4 167 
#define  OPTION_MIPS5 166 
#define  OPTION_MIPS64 165 
#define  OPTION_MIPS64R2 164 
#define  OPTION_MNO_7000_HILO_FIX 163 
#define  OPTION_MNO_SHARED 162 
#define  OPTION_MNO_SYM32 161 
#define  OPTION_MOCTEON_UNSUPPORTED 160 
#define  OPTION_MOCTEON_USEUN 159 
#define  OPTION_MSHARED 158 
#define  OPTION_MSYM32 157 
#define  OPTION_MT 156 
#define  OPTION_MTUNE 155 
#define  OPTION_MVXWORKS_PIC 154 
#define  OPTION_N32 153 
#define  OPTION_NON_SHARED 152 
#define  OPTION_NO_CONSTRUCT_FLOATS 151 
#define  OPTION_NO_DSP 150 
#define  OPTION_NO_DSPR2 149 
#define  OPTION_NO_FIX_VR4120 148 
#define  OPTION_NO_FIX_VR4130 147 
#define  OPTION_NO_M3900 146 
#define  OPTION_NO_M4010 145 
#define  OPTION_NO_M4100 144 
#define  OPTION_NO_M4650 143 
#define  OPTION_NO_MDEBUG 142 
#define  OPTION_NO_MDMX 141 
#define  OPTION_NO_MIPS16 140 
#define  OPTION_NO_MIPS3D 139 
#define  OPTION_NO_MOCTEON_UNSUPPORTED 138 
#define  OPTION_NO_MOCTEON_USEUN 137 
#define  OPTION_NO_MT 136 
#define  OPTION_NO_PDR 135 
#define  OPTION_NO_RELAX_BRANCH 134 
#define  OPTION_NO_SMARTMIPS 133 
#define  OPTION_PDR 132 
#define  OPTION_RELAX_BRANCH 131 
#define  OPTION_SMARTMIPS 130 
#define  OPTION_TRAP 129 
#define  OPTION_XGOT 128 
 int /*<<< orphan*/  SVR4_PIC ; 
 void* TRUE ; 
 int /*<<< orphan*/  VXWORKS_PIC ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,...) ; 
 void* atoi (char*) ; 
 int file_mips_fp32 ; 
 int file_mips_gp32 ; 
 int /*<<< orphan*/  file_mips_isa ; 
 int g_switch_seen ; 
 void* g_switch_value ; 
 void* mips_7000_hilo_fix ; 
 int /*<<< orphan*/  mips_abi ; 
 void* mips_abicalls ; 
 int /*<<< orphan*/  mips_arch_string ; 
 int mips_big_got ; 
 int mips_debug ; 
 int mips_disable_float_construction ; 
 int mips_fix_vr4120 ; 
 int mips_fix_vr4130 ; 
 void* mips_flag_mdebug ; 
 void* mips_flag_pdr ; 
 void* mips_in_shared ; 
 int /*<<< orphan*/  mips_no_prev_insn () ; 
 int mips_optimize ; 
 TYPE_1__ mips_opts ; 
 int /*<<< orphan*/  mips_pic ; 
 int mips_relax_branch ; 
 int /*<<< orphan*/  mips_set_option_string (int /*<<< orphan*/ *,char*) ; 
 int mips_trap ; 
 int /*<<< orphan*/  mips_tune_string ; 
 int octeon_error_on_unsupported ; 
 int octeon_use_unalign ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  support_64bit_objects () ; 
 int target_big_endian ; 

int
md_parse_option (int c, char *arg)
{
  switch (c)
    {
    case OPTION_CONSTRUCT_FLOATS:
      mips_disable_float_construction = 0;
      break;

    case OPTION_NO_CONSTRUCT_FLOATS:
      mips_disable_float_construction = 1;
      break;

    case OPTION_TRAP:
      mips_trap = 1;
      break;

    case OPTION_BREAK:
      mips_trap = 0;
      break;

    case OPTION_EB:
      target_big_endian = 1;
      break;

    case OPTION_EL:
      target_big_endian = 0;
      break;

    case OPTION_MOCTEON_UNSUPPORTED:
      octeon_error_on_unsupported = 1;
      break;

    case OPTION_NO_MOCTEON_UNSUPPORTED:
      octeon_error_on_unsupported = 0;
      break;

    case OPTION_MOCTEON_USEUN:
      octeon_use_unalign = 1;
      break;

    case OPTION_NO_MOCTEON_USEUN:
      octeon_use_unalign = 0;
      break;

    case 'O':
      if (arg && arg[0] == '0')
	mips_optimize = 1;
      else
	mips_optimize = 2;
      break;

    case 'g':
      if (arg == NULL)
	mips_debug = 2;
      else
	mips_debug = atoi (arg);
      break;

    case OPTION_MIPS1:
      file_mips_isa = ISA_MIPS1;
      break;

    case OPTION_MIPS2:
      file_mips_isa = ISA_MIPS2;
      break;

    case OPTION_MIPS3:
      file_mips_isa = ISA_MIPS3;
      break;

    case OPTION_MIPS4:
      file_mips_isa = ISA_MIPS4;
      break;

    case OPTION_MIPS5:
      file_mips_isa = ISA_MIPS5;
      break;

    case OPTION_MIPS32:
      file_mips_isa = ISA_MIPS32;
      break;

    case OPTION_MIPS32R2:
      file_mips_isa = ISA_MIPS32R2;
      break;

    case OPTION_MIPS64R2:
      file_mips_isa = ISA_MIPS64R2;
      break;

    case OPTION_MIPS64:
      file_mips_isa = ISA_MIPS64;
      break;

    case OPTION_MTUNE:
      mips_set_option_string (&mips_tune_string, arg);
      break;

    case OPTION_MARCH:
      mips_set_option_string (&mips_arch_string, arg);
      break;

    case OPTION_M4650:
      mips_set_option_string (&mips_arch_string, "4650");
      mips_set_option_string (&mips_tune_string, "4650");
      break;

    case OPTION_NO_M4650:
      break;

    case OPTION_M4010:
      mips_set_option_string (&mips_arch_string, "4010");
      mips_set_option_string (&mips_tune_string, "4010");
      break;

    case OPTION_NO_M4010:
      break;

    case OPTION_M4100:
      mips_set_option_string (&mips_arch_string, "4100");
      mips_set_option_string (&mips_tune_string, "4100");
      break;

    case OPTION_NO_M4100:
      break;

    case OPTION_M3900:
      mips_set_option_string (&mips_arch_string, "3900");
      mips_set_option_string (&mips_tune_string, "3900");
      break;

    case OPTION_NO_M3900:
      break;

    case OPTION_MDMX:
      mips_opts.ase_mdmx = 1;
      break;

    case OPTION_NO_MDMX:
      mips_opts.ase_mdmx = 0;
      break;

    case OPTION_DSP:
      mips_opts.ase_dsp = 1;
      mips_opts.ase_dspr2 = 0;
      break;

    case OPTION_NO_DSP:
      mips_opts.ase_dsp = 0;
      mips_opts.ase_dspr2 = 0;
      break;

    case OPTION_DSPR2:
      mips_opts.ase_dspr2 = 1;
      mips_opts.ase_dsp = 1;
      break;

    case OPTION_NO_DSPR2:
      mips_opts.ase_dspr2 = 0;
      mips_opts.ase_dsp = 0;
      break;

    case OPTION_MT:
      mips_opts.ase_mt = 1;
      break;

    case OPTION_NO_MT:
      mips_opts.ase_mt = 0;
      break;

    case OPTION_MIPS16:
      mips_opts.mips16 = 1;
      mips_no_prev_insn ();
      break;

    case OPTION_NO_MIPS16:
      mips_opts.mips16 = 0;
      mips_no_prev_insn ();
      break;

    case OPTION_MIPS3D:
      mips_opts.ase_mips3d = 1;
      break;

    case OPTION_NO_MIPS3D:
      mips_opts.ase_mips3d = 0;
      break;

    case OPTION_SMARTMIPS:
      mips_opts.ase_smartmips = 1;
      break;

    case OPTION_NO_SMARTMIPS:
      mips_opts.ase_smartmips = 0;
      break;

    case OPTION_FIX_VR4120:
      mips_fix_vr4120 = 1;
      break;

    case OPTION_NO_FIX_VR4120:
      mips_fix_vr4120 = 0;
      break;

    case OPTION_FIX_VR4130:
      mips_fix_vr4130 = 1;
      break;

    case OPTION_NO_FIX_VR4130:
      mips_fix_vr4130 = 0;
      break;

    case OPTION_RELAX_BRANCH:
      mips_relax_branch = 1;
      break;

    case OPTION_NO_RELAX_BRANCH:
      mips_relax_branch = 0;
      break;

    case OPTION_MSHARED:
      mips_in_shared = TRUE;
      break;

    case OPTION_MNO_SHARED:
      mips_in_shared = FALSE;
      break;

    case OPTION_MSYM32:
      mips_opts.sym32 = TRUE;
      break;

    case OPTION_MNO_SYM32:
      mips_opts.sym32 = FALSE;
      break;

#ifdef OBJ_ELF
      /* When generating ELF code, we permit -KPIC and -call_shared to
	 select SVR4_PIC, and -non_shared to select no PIC.  This is
	 intended to be compatible with Irix 5.  */
    case OPTION_CALL_SHARED:
      if (!IS_ELF)
	{
	  as_bad (_("-call_shared is supported only for ELF format"));
	  return 0;
	}
      mips_pic = SVR4_PIC;
      mips_abicalls = TRUE;
      break;

    case OPTION_NON_SHARED:
      if (!IS_ELF)
	{
	  as_bad (_("-non_shared is supported only for ELF format"));
	  return 0;
	}
      mips_pic = NO_PIC;
      mips_abicalls = FALSE;
      break;

      /* The -xgot option tells the assembler to use 32 bit offsets
         when accessing the got in SVR4_PIC mode.  It is for Irix
         compatibility.  */
    case OPTION_XGOT:
      mips_big_got = 1;
      break;
#endif /* OBJ_ELF */

    case 'G':
      g_switch_value = atoi (arg);
      g_switch_seen = 1;
      break;

#ifdef OBJ_ELF
      /* The -32, -n32 and -64 options are shortcuts for -mabi=32, -mabi=n32
	 and -mabi=64.  */
    case OPTION_32:
      if (!IS_ELF)
	{
	  as_bad (_("-32 is supported for ELF format only"));
	  return 0;
	}
      mips_abi = O32_ABI;
      break;

    case OPTION_N32:
      if (!IS_ELF)
	{
	  as_bad (_("-n32 is supported for ELF format only"));
	  return 0;
	}
      mips_abi = N32_ABI;
      break;

    case OPTION_64:
      if (!IS_ELF)
	{
	  as_bad (_("-64 is supported for ELF format only"));
	  return 0;
	}
      mips_abi = N64_ABI;
      if (!support_64bit_objects())
	as_fatal (_("No compiled in support for 64 bit object file format"));
      break;
#endif /* OBJ_ELF */

    case OPTION_GP32:
      file_mips_gp32 = 1;
      break;

    case OPTION_GP64:
      file_mips_gp32 = 0;
      break;

    case OPTION_FP32:
      file_mips_fp32 = 1;
      break;

    case OPTION_FP64:
      file_mips_fp32 = 0;
      break;

#ifdef OBJ_ELF
    case OPTION_MABI:
      if (!IS_ELF)
	{
	  as_bad (_("-mabi is supported for ELF format only"));
	  return 0;
	}
      if (strcmp (arg, "32") == 0)
	mips_abi = O32_ABI;
      else if (strcmp (arg, "o64") == 0)
	mips_abi = O64_ABI;
      else if (strcmp (arg, "n32") == 0)
	mips_abi = N32_ABI;
      else if (strcmp (arg, "64") == 0)
	{
	  mips_abi = N64_ABI;
	  if (! support_64bit_objects())
	    as_fatal (_("No compiled in support for 64 bit object file "
			"format"));
	}
      else if (strcmp (arg, "eabi") == 0)
	mips_abi = EABI_ABI;
      else
	{
	  as_fatal (_("invalid abi -mabi=%s"), arg);
	  return 0;
	}
      break;
#endif /* OBJ_ELF */

    case OPTION_M7000_HILO_FIX:
      mips_7000_hilo_fix = TRUE;
      break;

    case OPTION_MNO_7000_HILO_FIX:
      mips_7000_hilo_fix = FALSE;
      break;

#ifdef OBJ_ELF
    case OPTION_MDEBUG:
      mips_flag_mdebug = TRUE;
      break;

    case OPTION_NO_MDEBUG:
      mips_flag_mdebug = FALSE;
      break;

    case OPTION_PDR:
      mips_flag_pdr = TRUE;
      break;

    case OPTION_NO_PDR:
      mips_flag_pdr = FALSE;
      break;

    case OPTION_MVXWORKS_PIC:
      mips_pic = VXWORKS_PIC;
      break;
#endif /* OBJ_ELF */

    default:
      return 0;
    }

  return 1;
}