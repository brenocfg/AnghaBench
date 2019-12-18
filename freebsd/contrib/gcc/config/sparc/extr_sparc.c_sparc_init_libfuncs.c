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
 int /*<<< orphan*/  DFmode ; 
 scalar_t__ DITF_CONVERSION_LIBFUNCS ; 
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  SFmode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ SUN_CONVERSION_LIBFUNCS ; 
 scalar_t__ SUN_INTEGER_MULTIPLY_64 ; 
 scalar_t__ TARGET_ARCH32 ; 
 scalar_t__ TARGET_ARCH64 ; 
 scalar_t__ TARGET_FPU ; 
 int /*<<< orphan*/  TFmode ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  eq_optab ; 
 int /*<<< orphan*/  ge_optab ; 
 int /*<<< orphan*/  gofast_maybe_init_libfuncs () ; 
 int /*<<< orphan*/  gt_optab ; 
 int /*<<< orphan*/  le_optab ; 
 int /*<<< orphan*/  lt_optab ; 
 int /*<<< orphan*/  ne_optab ; 
 int /*<<< orphan*/  neg_optab ; 
 int /*<<< orphan*/  sdiv_optab ; 
 int /*<<< orphan*/  set_conv_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_optab_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sext_optab ; 
 int /*<<< orphan*/  sfix_optab ; 
 int /*<<< orphan*/  sfloat_optab ; 
 int /*<<< orphan*/  smod_optab ; 
 int /*<<< orphan*/  smul_optab ; 
 int /*<<< orphan*/  sqrt_optab ; 
 int /*<<< orphan*/  sub_optab ; 
 int /*<<< orphan*/  trunc_optab ; 
 int /*<<< orphan*/  udiv_optab ; 
 int /*<<< orphan*/  ufix_optab ; 
 int /*<<< orphan*/  ufloat_optab ; 
 int /*<<< orphan*/  umod_optab ; 

__attribute__((used)) static void
sparc_init_libfuncs (void)
{
  if (TARGET_ARCH32)
    {
      /* Use the subroutines that Sun's library provides for integer
	 multiply and divide.  The `*' prevents an underscore from
	 being prepended by the compiler. .umul is a little faster
	 than .mul.  */
      set_optab_libfunc (smul_optab, SImode, "*.umul");
      set_optab_libfunc (sdiv_optab, SImode, "*.div");
      set_optab_libfunc (udiv_optab, SImode, "*.udiv");
      set_optab_libfunc (smod_optab, SImode, "*.rem");
      set_optab_libfunc (umod_optab, SImode, "*.urem");

      /* TFmode arithmetic.  These names are part of the SPARC 32bit ABI.  */
      set_optab_libfunc (add_optab, TFmode, "_Q_add");
      set_optab_libfunc (sub_optab, TFmode, "_Q_sub");
      set_optab_libfunc (neg_optab, TFmode, "_Q_neg");
      set_optab_libfunc (smul_optab, TFmode, "_Q_mul");
      set_optab_libfunc (sdiv_optab, TFmode, "_Q_div");

      /* We can define the TFmode sqrt optab only if TARGET_FPU.  This
	 is because with soft-float, the SFmode and DFmode sqrt
	 instructions will be absent, and the compiler will notice and
	 try to use the TFmode sqrt instruction for calls to the
	 builtin function sqrt, but this fails.  */
      if (TARGET_FPU)
	set_optab_libfunc (sqrt_optab, TFmode, "_Q_sqrt");

      set_optab_libfunc (eq_optab, TFmode, "_Q_feq");
      set_optab_libfunc (ne_optab, TFmode, "_Q_fne");
      set_optab_libfunc (gt_optab, TFmode, "_Q_fgt");
      set_optab_libfunc (ge_optab, TFmode, "_Q_fge");
      set_optab_libfunc (lt_optab, TFmode, "_Q_flt");
      set_optab_libfunc (le_optab, TFmode, "_Q_fle");

      set_conv_libfunc (sext_optab,   TFmode, SFmode, "_Q_stoq");
      set_conv_libfunc (sext_optab,   TFmode, DFmode, "_Q_dtoq");
      set_conv_libfunc (trunc_optab,  SFmode, TFmode, "_Q_qtos");
      set_conv_libfunc (trunc_optab,  DFmode, TFmode, "_Q_qtod");

      set_conv_libfunc (sfix_optab,   SImode, TFmode, "_Q_qtoi");
      set_conv_libfunc (ufix_optab,   SImode, TFmode, "_Q_qtou");
      set_conv_libfunc (sfloat_optab, TFmode, SImode, "_Q_itoq");
      set_conv_libfunc (ufloat_optab, TFmode, SImode, "_Q_utoq");

      if (DITF_CONVERSION_LIBFUNCS)
	{
	  set_conv_libfunc (sfix_optab,   DImode, TFmode, "_Q_qtoll");
	  set_conv_libfunc (ufix_optab,   DImode, TFmode, "_Q_qtoull");
	  set_conv_libfunc (sfloat_optab, TFmode, DImode, "_Q_lltoq");
	  set_conv_libfunc (ufloat_optab, TFmode, DImode, "_Q_ulltoq");
	}

      if (SUN_CONVERSION_LIBFUNCS)
	{
	  set_conv_libfunc (sfix_optab, DImode, SFmode, "__ftoll");
	  set_conv_libfunc (ufix_optab, DImode, SFmode, "__ftoull");
	  set_conv_libfunc (sfix_optab, DImode, DFmode, "__dtoll");
	  set_conv_libfunc (ufix_optab, DImode, DFmode, "__dtoull");
	}
    }
  if (TARGET_ARCH64)
    {
      /* In the SPARC 64bit ABI, SImode multiply and divide functions
	 do not exist in the library.  Make sure the compiler does not
	 emit calls to them by accident.  (It should always use the
         hardware instructions.)  */
      set_optab_libfunc (smul_optab, SImode, 0);
      set_optab_libfunc (sdiv_optab, SImode, 0);
      set_optab_libfunc (udiv_optab, SImode, 0);
      set_optab_libfunc (smod_optab, SImode, 0);
      set_optab_libfunc (umod_optab, SImode, 0);

      if (SUN_INTEGER_MULTIPLY_64)
	{
	  set_optab_libfunc (smul_optab, DImode, "__mul64");
	  set_optab_libfunc (sdiv_optab, DImode, "__div64");
	  set_optab_libfunc (udiv_optab, DImode, "__udiv64");
	  set_optab_libfunc (smod_optab, DImode, "__rem64");
	  set_optab_libfunc (umod_optab, DImode, "__urem64");
	}

      if (SUN_CONVERSION_LIBFUNCS)
	{
	  set_conv_libfunc (sfix_optab, DImode, SFmode, "__ftol");
	  set_conv_libfunc (ufix_optab, DImode, SFmode, "__ftoul");
	  set_conv_libfunc (sfix_optab, DImode, DFmode, "__dtol");
	  set_conv_libfunc (ufix_optab, DImode, DFmode, "__dtoul");
	}
    }

  gofast_maybe_init_libfuncs ();
}