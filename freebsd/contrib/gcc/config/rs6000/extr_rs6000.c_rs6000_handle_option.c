#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int aix_struct_ret; int isel; int spe; int abi; int ieee; int float_gprs; int long_double; int alignment; } ;
struct TYPE_3__ {char const* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABI_DARWIN ; 
 int /*<<< orphan*/  DEFAULT_ABI ; 
 int /*<<< orphan*/  MASK_ALIGN_NATURAL ; 
 int /*<<< orphan*/  MASK_ALIGN_POWER ; 
 int MASK_MINIMAL_TOC ; 
 int MASK_MULTIPLE ; 
 int MASK_POWER ; 
 int MASK_POWER2 ; 
 int MASK_POWERPC ; 
 int MASK_POWERPC64 ; 
 int MASK_PPC_GFXOPT ; 
 int MASK_PPC_GPOPT ; 
 int MASK_RELOCATABLE ; 
 int MASK_STRING ; 
#define  OPT_m32 160 
#define  OPT_m64 159 
#define  OPT_mabi_ 158 
#define  OPT_maix32 157 
#define  OPT_maix64 156 
#define  OPT_maix_struct_return 155 
#define  OPT_malign_ 154 
#define  OPT_mcall_ 153 
#define  OPT_mcpu_ 152 
#define  OPT_mdebug_ 151 
#define  OPT_mfloat_gprs_ 150 
#define  OPT_mfull_toc 149 
#define  OPT_minsert_sched_nops_ 148 
#define  OPT_misel_ 147 
#define  OPT_mlong_double_ 146 
#define  OPT_mminimal_toc 145 
#define  OPT_mno_power 144 
#define  OPT_mno_powerpc 143 
#define  OPT_mpower 142 
#define  OPT_mpower2 141 
#define  OPT_mpowerpc_gfxopt 140 
#define  OPT_mpowerpc_gpopt 139 
#define  OPT_mrelocatable 138 
#define  OPT_mrelocatable_lib 137 
#define  OPT_msched_costly_dep_ 136 
#define  OPT_msdata_ 135 
#define  OPT_mspe_ 134 
#define  OPT_msvr4_struct_return 133 
#define  OPT_mtls_size_ 132 
#define  OPT_mtoc 131 
#define  OPT_mtraceback_ 130 
#define  OPT_mtune_ 129 
#define  OPT_mvrsave_ 128 
 int RS6000_DEFAULT_LONG_DOUBLE_SIZE ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_ALTIVEC_VRSAVE ; 
 int TARGET_NO_FP_IN_TOC ; 
 int /*<<< orphan*/  TARGET_NO_SUM_IN_TOC ; 
 int /*<<< orphan*/  TARGET_SPE_ABI ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 char const* rs6000_abi_name ; 
 int /*<<< orphan*/  rs6000_alignment_flags ; 
 int rs6000_altivec_abi ; 
 int rs6000_darwin64_abi ; 
 char const* rs6000_debug_name ; 
 TYPE_2__ rs6000_explicit_options ; 
 int rs6000_float_gprs ; 
 int rs6000_ieeequad ; 
 int /*<<< orphan*/  rs6000_isel ; 
 int rs6000_long_double_type_size ; 
 int /*<<< orphan*/  rs6000_parse_yes_no_option (char*,char const*,int /*<<< orphan*/ *) ; 
 char const* rs6000_sched_costly_dep_str ; 
 char const* rs6000_sched_insert_nops_str ; 
 char const* rs6000_sdata_name ; 
 TYPE_1__* rs6000_select ; 
 int /*<<< orphan*/  rs6000_spe ; 
 int rs6000_spe_abi ; 
 char const* rs6000_tls_size_string ; 
 char const* rs6000_traceback_name ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int target_flags ; 
 int target_flags_explicit ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
rs6000_handle_option (size_t code, const char *arg, int value)
{
  switch (code)
    {
    case OPT_mno_power:
      target_flags &= ~(MASK_POWER | MASK_POWER2
			| MASK_MULTIPLE | MASK_STRING);
      target_flags_explicit |= (MASK_POWER | MASK_POWER2
				| MASK_MULTIPLE | MASK_STRING);
      break;
    case OPT_mno_powerpc:
      target_flags &= ~(MASK_POWERPC | MASK_PPC_GPOPT
			| MASK_PPC_GFXOPT | MASK_POWERPC64);
      target_flags_explicit |= (MASK_POWERPC | MASK_PPC_GPOPT
				| MASK_PPC_GFXOPT | MASK_POWERPC64);
      break;
    case OPT_mfull_toc:
      target_flags &= ~MASK_MINIMAL_TOC;
      TARGET_NO_FP_IN_TOC = 0;
      TARGET_NO_SUM_IN_TOC = 0;
      target_flags_explicit |= MASK_MINIMAL_TOC;
#ifdef TARGET_USES_SYSV4_OPT
      /* Note, V.4 no longer uses a normal TOC, so make -mfull-toc, be
	 just the same as -mminimal-toc.  */
      target_flags |= MASK_MINIMAL_TOC;
      target_flags_explicit |= MASK_MINIMAL_TOC;
#endif
      break;

#ifdef TARGET_USES_SYSV4_OPT
    case OPT_mtoc:
      /* Make -mtoc behave like -mminimal-toc.  */
      target_flags |= MASK_MINIMAL_TOC;
      target_flags_explicit |= MASK_MINIMAL_TOC;
      break;
#endif

#ifdef TARGET_USES_AIX64_OPT
    case OPT_maix64:
#else
    case OPT_m64:
#endif
      target_flags |= MASK_POWERPC64 | MASK_POWERPC;
      target_flags |= ~target_flags_explicit & MASK_PPC_GFXOPT;
      target_flags_explicit |= MASK_POWERPC64 | MASK_POWERPC;
      break;

#ifdef TARGET_USES_AIX64_OPT
    case OPT_maix32:
#else
    case OPT_m32:
#endif
      target_flags &= ~MASK_POWERPC64;
      target_flags_explicit |= MASK_POWERPC64;
      break;

    case OPT_minsert_sched_nops_:
      rs6000_sched_insert_nops_str = arg;
      break;

    case OPT_mminimal_toc:
      if (value == 1)
	{
	  TARGET_NO_FP_IN_TOC = 0;
	  TARGET_NO_SUM_IN_TOC = 0;
	}
      break;

    case OPT_mpower:
      if (value == 1)
	{
	  target_flags |= (MASK_MULTIPLE | MASK_STRING);
	  target_flags_explicit |= (MASK_MULTIPLE | MASK_STRING);
	}
      break;

    case OPT_mpower2:
      if (value == 1)
	{
	  target_flags |= (MASK_POWER | MASK_MULTIPLE | MASK_STRING);
	  target_flags_explicit |= (MASK_POWER | MASK_MULTIPLE | MASK_STRING);
	}
      break;

    case OPT_mpowerpc_gpopt:
    case OPT_mpowerpc_gfxopt:
      if (value == 1)
	{
	  target_flags |= MASK_POWERPC;
	  target_flags_explicit |= MASK_POWERPC;
	}
      break;

    case OPT_maix_struct_return:
    case OPT_msvr4_struct_return:
      rs6000_explicit_options.aix_struct_ret = true;
      break;

    case OPT_mvrsave_:
      rs6000_parse_yes_no_option ("vrsave", arg, &(TARGET_ALTIVEC_VRSAVE));
      break;

    case OPT_misel_:
      rs6000_explicit_options.isel = true;
      rs6000_parse_yes_no_option ("isel", arg, &(rs6000_isel));
      break;

    case OPT_mspe_:
      rs6000_explicit_options.spe = true;
      rs6000_parse_yes_no_option ("spe", arg, &(rs6000_spe));
      /* No SPE means 64-bit long doubles, even if an E500.  */
      if (!rs6000_spe)
	rs6000_long_double_type_size = 64;
      break;

    case OPT_mdebug_:
      rs6000_debug_name = arg;
      break;

#ifdef TARGET_USES_SYSV4_OPT
    case OPT_mcall_:
      rs6000_abi_name = arg;
      break;

    case OPT_msdata_:
      rs6000_sdata_name = arg;
      break;

    case OPT_mtls_size_:
      rs6000_tls_size_string = arg;
      break;

    case OPT_mrelocatable:
      if (value == 1)
	{
	  target_flags |= MASK_MINIMAL_TOC;
	  target_flags_explicit |= MASK_MINIMAL_TOC;
	  TARGET_NO_FP_IN_TOC = 1;
	}
      break;

    case OPT_mrelocatable_lib:
      if (value == 1)
	{
	  target_flags |= MASK_RELOCATABLE | MASK_MINIMAL_TOC;
	  target_flags_explicit |= MASK_RELOCATABLE | MASK_MINIMAL_TOC;
	  TARGET_NO_FP_IN_TOC = 1;
	}
      else
	{
	  target_flags &= ~MASK_RELOCATABLE;
	  target_flags_explicit |= MASK_RELOCATABLE;
	}
      break;
#endif

    case OPT_mabi_:
      if (!strcmp (arg, "altivec"))
	{
	  rs6000_explicit_options.abi = true;
	  rs6000_altivec_abi = 1;
	  rs6000_spe_abi = 0;
	}
      else if (! strcmp (arg, "no-altivec"))
	{
	  /* ??? Don't set rs6000_explicit_options.abi here, to allow
	     the default for rs6000_spe_abi to be chosen later.  */
	  rs6000_altivec_abi = 0;
	}
      else if (! strcmp (arg, "spe"))
	{
	  rs6000_explicit_options.abi = true;
	  rs6000_spe_abi = 1;
	  rs6000_altivec_abi = 0;
	  if (!TARGET_SPE_ABI)
	    error ("not configured for ABI: '%s'", arg);
	}
      else if (! strcmp (arg, "no-spe"))
	{
	  rs6000_explicit_options.abi = true;
	  rs6000_spe_abi = 0;
	}

      /* These are here for testing during development only, do not
	 document in the manual please.  */
      else if (! strcmp (arg, "d64"))
	{
	  rs6000_darwin64_abi = 1;
	  warning (0, "Using darwin64 ABI");
	}
      else if (! strcmp (arg, "d32"))
	{
	  rs6000_darwin64_abi = 0;
	  warning (0, "Using old darwin ABI");
	}

      else if (! strcmp (arg, "ibmlongdouble"))
	{
	  rs6000_explicit_options.ieee = true;
	  rs6000_ieeequad = 0;
	  warning (0, "Using IBM extended precision long double");
	}
      else if (! strcmp (arg, "ieeelongdouble"))
	{
	  rs6000_explicit_options.ieee = true;
	  rs6000_ieeequad = 1;
	  warning (0, "Using IEEE extended precision long double");
	}

      else
	{
	  error ("unknown ABI specified: '%s'", arg);
	  return false;
	}
      break;

    case OPT_mcpu_:
      rs6000_select[1].string = arg;
      break;

    case OPT_mtune_:
      rs6000_select[2].string = arg;
      break;

    case OPT_mtraceback_:
      rs6000_traceback_name = arg;
      break;

    case OPT_mfloat_gprs_:
      rs6000_explicit_options.float_gprs = true;
      if (! strcmp (arg, "yes") || ! strcmp (arg, "single"))
	rs6000_float_gprs = 1;
      else if (! strcmp (arg, "double"))
	rs6000_float_gprs = 2;
      else if (! strcmp (arg, "no"))
	rs6000_float_gprs = 0;
      else
	{
	  error ("invalid option for -mfloat-gprs: '%s'", arg);
	  return false;
	}
      break;

    case OPT_mlong_double_:
      rs6000_explicit_options.long_double = true;
      rs6000_long_double_type_size = RS6000_DEFAULT_LONG_DOUBLE_SIZE;
      if (value != 64 && value != 128)
	{
	  error ("Unknown switch -mlong-double-%s", arg);
	  rs6000_long_double_type_size = RS6000_DEFAULT_LONG_DOUBLE_SIZE;
	  return false;
	}
      else
	rs6000_long_double_type_size = value;
      break;

    case OPT_msched_costly_dep_:
      rs6000_sched_costly_dep_str = arg;
      break;

    case OPT_malign_:
      rs6000_explicit_options.alignment = true;
      if (! strcmp (arg, "power"))
	{
	  /* On 64-bit Darwin, power alignment is ABI-incompatible with
	     some C library functions, so warn about it. The flag may be
	     useful for performance studies from time to time though, so
	     don't disable it entirely.  */
	  if (DEFAULT_ABI == ABI_DARWIN && TARGET_64BIT)
	    warning (0, "-malign-power is not supported for 64-bit Darwin;"
		     " it is incompatible with the installed C and C++ libraries");
	  rs6000_alignment_flags = MASK_ALIGN_POWER;
	}
      else if (! strcmp (arg, "natural"))
	rs6000_alignment_flags = MASK_ALIGN_NATURAL;
      else
	{
	  error ("unknown -malign-XXXXX option specified: '%s'", arg);
	  return false;
	}
      break;
    }
  return true;
}