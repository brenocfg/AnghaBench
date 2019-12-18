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
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  SFmode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_BPABI ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  ashl_optab ; 
 int /*<<< orphan*/  ashr_optab ; 
 int /*<<< orphan*/  cmp_optab ; 
 int /*<<< orphan*/  eq_optab ; 
 int /*<<< orphan*/  ge_optab ; 
 int /*<<< orphan*/  gt_optab ; 
 int /*<<< orphan*/  le_optab ; 
 int /*<<< orphan*/  lshr_optab ; 
 int /*<<< orphan*/  lt_optab ; 
 int /*<<< orphan*/  ne_optab ; 
 int /*<<< orphan*/  neg_optab ; 
 int /*<<< orphan*/  sdiv_optab ; 
 int /*<<< orphan*/  sdivmod_optab ; 
 int /*<<< orphan*/  set_conv_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_optab_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sext_optab ; 
 int /*<<< orphan*/  sfix_optab ; 
 int /*<<< orphan*/  sfloat_optab ; 
 int /*<<< orphan*/  smod_optab ; 
 int /*<<< orphan*/  smul_optab ; 
 int /*<<< orphan*/  sub_optab ; 
 int /*<<< orphan*/  trunc_optab ; 
 int /*<<< orphan*/  ucmp_optab ; 
 int /*<<< orphan*/  udiv_optab ; 
 int /*<<< orphan*/  udivmod_optab ; 
 int /*<<< orphan*/  ufix_optab ; 
 int /*<<< orphan*/  ufloat_optab ; 
 int /*<<< orphan*/  umod_optab ; 
 int /*<<< orphan*/  unord_optab ; 

__attribute__((used)) static void
arm_init_libfuncs (void)
{
  /* There are no special library functions unless we are using the
     ARM BPABI.  */
  if (!TARGET_BPABI)
    return;

  /* The functions below are described in Section 4 of the "Run-Time
     ABI for the ARM architecture", Version 1.0.  */

  /* Double-precision floating-point arithmetic.  Table 2.  */
  set_optab_libfunc (add_optab, DFmode, "__aeabi_dadd");
  set_optab_libfunc (sdiv_optab, DFmode, "__aeabi_ddiv");
  set_optab_libfunc (smul_optab, DFmode, "__aeabi_dmul");
  set_optab_libfunc (neg_optab, DFmode, "__aeabi_dneg");
  set_optab_libfunc (sub_optab, DFmode, "__aeabi_dsub");

  /* Double-precision comparisons.  Table 3.  */
  set_optab_libfunc (eq_optab, DFmode, "__aeabi_dcmpeq");
  set_optab_libfunc (ne_optab, DFmode, NULL);
  set_optab_libfunc (lt_optab, DFmode, "__aeabi_dcmplt");
  set_optab_libfunc (le_optab, DFmode, "__aeabi_dcmple");
  set_optab_libfunc (ge_optab, DFmode, "__aeabi_dcmpge");
  set_optab_libfunc (gt_optab, DFmode, "__aeabi_dcmpgt");
  set_optab_libfunc (unord_optab, DFmode, "__aeabi_dcmpun");

  /* Single-precision floating-point arithmetic.  Table 4.  */
  set_optab_libfunc (add_optab, SFmode, "__aeabi_fadd");
  set_optab_libfunc (sdiv_optab, SFmode, "__aeabi_fdiv");
  set_optab_libfunc (smul_optab, SFmode, "__aeabi_fmul");
  set_optab_libfunc (neg_optab, SFmode, "__aeabi_fneg");
  set_optab_libfunc (sub_optab, SFmode, "__aeabi_fsub");

  /* Single-precision comparisons.  Table 5.  */
  set_optab_libfunc (eq_optab, SFmode, "__aeabi_fcmpeq");
  set_optab_libfunc (ne_optab, SFmode, NULL);
  set_optab_libfunc (lt_optab, SFmode, "__aeabi_fcmplt");
  set_optab_libfunc (le_optab, SFmode, "__aeabi_fcmple");
  set_optab_libfunc (ge_optab, SFmode, "__aeabi_fcmpge");
  set_optab_libfunc (gt_optab, SFmode, "__aeabi_fcmpgt");
  set_optab_libfunc (unord_optab, SFmode, "__aeabi_fcmpun");

  /* Floating-point to integer conversions.  Table 6.  */
  set_conv_libfunc (sfix_optab, SImode, DFmode, "__aeabi_d2iz");
  set_conv_libfunc (ufix_optab, SImode, DFmode, "__aeabi_d2uiz");
  set_conv_libfunc (sfix_optab, DImode, DFmode, "__aeabi_d2lz");
  set_conv_libfunc (ufix_optab, DImode, DFmode, "__aeabi_d2ulz");
  set_conv_libfunc (sfix_optab, SImode, SFmode, "__aeabi_f2iz");
  set_conv_libfunc (ufix_optab, SImode, SFmode, "__aeabi_f2uiz");
  set_conv_libfunc (sfix_optab, DImode, SFmode, "__aeabi_f2lz");
  set_conv_libfunc (ufix_optab, DImode, SFmode, "__aeabi_f2ulz");

  /* Conversions between floating types.  Table 7.  */
  set_conv_libfunc (trunc_optab, SFmode, DFmode, "__aeabi_d2f");
  set_conv_libfunc (sext_optab, DFmode, SFmode, "__aeabi_f2d");

  /* Integer to floating-point conversions.  Table 8.  */
  set_conv_libfunc (sfloat_optab, DFmode, SImode, "__aeabi_i2d");
  set_conv_libfunc (ufloat_optab, DFmode, SImode, "__aeabi_ui2d");
  set_conv_libfunc (sfloat_optab, DFmode, DImode, "__aeabi_l2d");
  set_conv_libfunc (ufloat_optab, DFmode, DImode, "__aeabi_ul2d");
  set_conv_libfunc (sfloat_optab, SFmode, SImode, "__aeabi_i2f");
  set_conv_libfunc (ufloat_optab, SFmode, SImode, "__aeabi_ui2f");
  set_conv_libfunc (sfloat_optab, SFmode, DImode, "__aeabi_l2f");
  set_conv_libfunc (ufloat_optab, SFmode, DImode, "__aeabi_ul2f");

  /* Long long.  Table 9.  */
  set_optab_libfunc (smul_optab, DImode, "__aeabi_lmul");
  set_optab_libfunc (sdivmod_optab, DImode, "__aeabi_ldivmod");
  set_optab_libfunc (udivmod_optab, DImode, "__aeabi_uldivmod");
  set_optab_libfunc (ashl_optab, DImode, "__aeabi_llsl");
  set_optab_libfunc (lshr_optab, DImode, "__aeabi_llsr");
  set_optab_libfunc (ashr_optab, DImode, "__aeabi_lasr");
  set_optab_libfunc (cmp_optab, DImode, "__aeabi_lcmp");
  set_optab_libfunc (ucmp_optab, DImode, "__aeabi_ulcmp");

  /* Integer (32/32->32) division.  \S 4.3.1.  */
  set_optab_libfunc (sdivmod_optab, SImode, "__aeabi_idivmod");
  set_optab_libfunc (udivmod_optab, SImode, "__aeabi_uidivmod");

  /* The divmod functions are designed so that they can be used for
     plain division, even though they return both the quotient and the
     remainder.  The quotient is returned in the usual location (i.e.,
     r0 for SImode, {r0, r1} for DImode), just as would be expected
     for an ordinary division routine.  Because the AAPCS calling
     conventions specify that all of { r0, r1, r2, r3 } are
     callee-saved registers, there is no need to tell the compiler
     explicitly that those registers are clobbered by these
     routines.  */
  set_optab_libfunc (sdiv_optab, DImode, "__aeabi_ldivmod");
  set_optab_libfunc (udiv_optab, DImode, "__aeabi_uldivmod");

  /* For SImode division the ABI provides div-without-mod routines,
     which are faster.  */
  set_optab_libfunc (sdiv_optab, SImode, "__aeabi_idiv");
  set_optab_libfunc (udiv_optab, SImode, "__aeabi_uidiv");

  /* We don't have mod libcalls.  Fortunately gcc knows how to use the
     divmod libcalls instead.  */
  set_optab_libfunc (smod_optab, DImode, NULL);
  set_optab_libfunc (umod_optab, DImode, NULL);
  set_optab_libfunc (smod_optab, SImode, NULL);
  set_optab_libfunc (umod_optab, SImode, NULL);
}