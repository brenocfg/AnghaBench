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
 int /*<<< orphan*/  SFmode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_DOUBLE_FLOAT ; 
 scalar_t__ TARGET_FIX_VR4120 ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  eq_optab ; 
 int /*<<< orphan*/  ge_optab ; 
 int /*<<< orphan*/  gofast_maybe_init_libfuncs () ; 
 int /*<<< orphan*/  gt_optab ; 
 int /*<<< orphan*/  le_optab ; 
 int /*<<< orphan*/  lt_optab ; 
 scalar_t__ mips16_hard_float ; 
 int /*<<< orphan*/  ne_optab ; 
 int /*<<< orphan*/  sdiv_optab ; 
 int /*<<< orphan*/  set_conv_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_optab_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sext_optab ; 
 int /*<<< orphan*/  sfix_optab ; 
 int /*<<< orphan*/  sfloat_optab ; 
 int /*<<< orphan*/  smod_optab ; 
 int /*<<< orphan*/  smul_optab ; 
 int /*<<< orphan*/  sub_optab ; 
 int /*<<< orphan*/  trunc_optab ; 

__attribute__((used)) static void
mips_init_libfuncs (void)
{
  if (TARGET_FIX_VR4120)
    {
      set_optab_libfunc (sdiv_optab, SImode, "__vr4120_divsi3");
      set_optab_libfunc (smod_optab, SImode, "__vr4120_modsi3");
    }

  if (TARGET_MIPS16 && mips16_hard_float)
    {
      set_optab_libfunc (add_optab, SFmode, "__mips16_addsf3");
      set_optab_libfunc (sub_optab, SFmode, "__mips16_subsf3");
      set_optab_libfunc (smul_optab, SFmode, "__mips16_mulsf3");
      set_optab_libfunc (sdiv_optab, SFmode, "__mips16_divsf3");

      set_optab_libfunc (eq_optab, SFmode, "__mips16_eqsf2");
      set_optab_libfunc (ne_optab, SFmode, "__mips16_nesf2");
      set_optab_libfunc (gt_optab, SFmode, "__mips16_gtsf2");
      set_optab_libfunc (ge_optab, SFmode, "__mips16_gesf2");
      set_optab_libfunc (lt_optab, SFmode, "__mips16_ltsf2");
      set_optab_libfunc (le_optab, SFmode, "__mips16_lesf2");

      set_conv_libfunc (sfix_optab, SImode, SFmode, "__mips16_fix_truncsfsi");
      set_conv_libfunc (sfloat_optab, SFmode, SImode, "__mips16_floatsisf");

      if (TARGET_DOUBLE_FLOAT)
	{
	  set_optab_libfunc (add_optab, DFmode, "__mips16_adddf3");
	  set_optab_libfunc (sub_optab, DFmode, "__mips16_subdf3");
	  set_optab_libfunc (smul_optab, DFmode, "__mips16_muldf3");
	  set_optab_libfunc (sdiv_optab, DFmode, "__mips16_divdf3");

	  set_optab_libfunc (eq_optab, DFmode, "__mips16_eqdf2");
	  set_optab_libfunc (ne_optab, DFmode, "__mips16_nedf2");
	  set_optab_libfunc (gt_optab, DFmode, "__mips16_gtdf2");
	  set_optab_libfunc (ge_optab, DFmode, "__mips16_gedf2");
	  set_optab_libfunc (lt_optab, DFmode, "__mips16_ltdf2");
	  set_optab_libfunc (le_optab, DFmode, "__mips16_ledf2");

	  set_conv_libfunc (sext_optab, DFmode, SFmode, "__mips16_extendsfdf2");
	  set_conv_libfunc (trunc_optab, SFmode, DFmode, "__mips16_truncdfsf2");

	  set_conv_libfunc (sfix_optab, SImode, DFmode, "__mips16_fix_truncdfsi");
	  set_conv_libfunc (sfloat_optab, DFmode, SImode, "__mips16_floatsidf");
	}
    }
  else
    gofast_maybe_init_libfuncs ();
}