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
 scalar_t__ ABI_V4 ; 
 scalar_t__ DEFAULT_ABI ; 
 int /*<<< orphan*/  DFmode ; 
 int /*<<< orphan*/  SFmode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_IEEEQUAD ; 
 scalar_t__ TARGET_POWER2 ; 
 int /*<<< orphan*/  TARGET_POWERPC ; 
 scalar_t__ TARGET_PPC_GPOPT ; 
 scalar_t__ TARGET_SOFT_FLOAT ; 
 scalar_t__ TARGET_XCOFF ; 
 int /*<<< orphan*/  TARGET_XL_COMPAT ; 
 int /*<<< orphan*/  TFmode ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  eq_optab ; 
 int /*<<< orphan*/  ge_optab ; 
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
 int /*<<< orphan*/  smul_optab ; 
 int /*<<< orphan*/  sqrt_optab ; 
 int /*<<< orphan*/  sub_optab ; 
 int /*<<< orphan*/  trunc_optab ; 
 int /*<<< orphan*/  ufix_optab ; 
 int /*<<< orphan*/  ufloat_optab ; 
 int /*<<< orphan*/  unord_optab ; 

__attribute__((used)) static void
rs6000_init_libfuncs (void)
{
  if (DEFAULT_ABI != ABI_V4 && TARGET_XCOFF
      && !TARGET_POWER2 && !TARGET_POWERPC)
    {
      /* AIX library routines for float->int conversion.  */
      set_conv_libfunc (sfix_optab, SImode, DFmode, "__itrunc");
      set_conv_libfunc (ufix_optab, SImode, DFmode, "__uitrunc");
      set_conv_libfunc (sfix_optab, SImode, TFmode, "_qitrunc");
      set_conv_libfunc (ufix_optab, SImode, TFmode, "_quitrunc");
    }

  if (!TARGET_IEEEQUAD)
      /* AIX/Darwin/64-bit Linux quad floating point routines.  */
    if (!TARGET_XL_COMPAT)
      {
	set_optab_libfunc (add_optab, TFmode, "__gcc_qadd");
	set_optab_libfunc (sub_optab, TFmode, "__gcc_qsub");
	set_optab_libfunc (smul_optab, TFmode, "__gcc_qmul");
	set_optab_libfunc (sdiv_optab, TFmode, "__gcc_qdiv");

	if (TARGET_SOFT_FLOAT)
	  {
	    set_optab_libfunc (neg_optab, TFmode, "__gcc_qneg");
	    set_optab_libfunc (eq_optab, TFmode, "__gcc_qeq");
	    set_optab_libfunc (ne_optab, TFmode, "__gcc_qne");
	    set_optab_libfunc (gt_optab, TFmode, "__gcc_qgt");
	    set_optab_libfunc (ge_optab, TFmode, "__gcc_qge");
	    set_optab_libfunc (lt_optab, TFmode, "__gcc_qlt");
	    set_optab_libfunc (le_optab, TFmode, "__gcc_qle");
	    set_optab_libfunc (unord_optab, TFmode, "__gcc_qunord");

	    set_conv_libfunc (sext_optab, TFmode, SFmode, "__gcc_stoq");
	    set_conv_libfunc (sext_optab, TFmode, DFmode, "__gcc_dtoq");
	    set_conv_libfunc (trunc_optab, SFmode, TFmode, "__gcc_qtos");
	    set_conv_libfunc (trunc_optab, DFmode, TFmode, "__gcc_qtod");
	    set_conv_libfunc (sfix_optab, SImode, TFmode, "__gcc_qtoi");
	    set_conv_libfunc (ufix_optab, SImode, TFmode, "__gcc_qtou");
	    set_conv_libfunc (sfloat_optab, TFmode, SImode, "__gcc_itoq");
	    set_conv_libfunc (ufloat_optab, TFmode, SImode, "__gcc_utoq");
	  }
      }
    else
      {
	set_optab_libfunc (add_optab, TFmode, "_xlqadd");
	set_optab_libfunc (sub_optab, TFmode, "_xlqsub");
	set_optab_libfunc (smul_optab, TFmode, "_xlqmul");
	set_optab_libfunc (sdiv_optab, TFmode, "_xlqdiv");
      }
  else
    {
      /* 32-bit SVR4 quad floating point routines.  */

      set_optab_libfunc (add_optab, TFmode, "_q_add");
      set_optab_libfunc (sub_optab, TFmode, "_q_sub");
      set_optab_libfunc (neg_optab, TFmode, "_q_neg");
      set_optab_libfunc (smul_optab, TFmode, "_q_mul");
      set_optab_libfunc (sdiv_optab, TFmode, "_q_div");
      if (TARGET_PPC_GPOPT || TARGET_POWER2)
	set_optab_libfunc (sqrt_optab, TFmode, "_q_sqrt");

      set_optab_libfunc (eq_optab, TFmode, "_q_feq");
      set_optab_libfunc (ne_optab, TFmode, "_q_fne");
      set_optab_libfunc (gt_optab, TFmode, "_q_fgt");
      set_optab_libfunc (ge_optab, TFmode, "_q_fge");
      set_optab_libfunc (lt_optab, TFmode, "_q_flt");
      set_optab_libfunc (le_optab, TFmode, "_q_fle");

      set_conv_libfunc (sext_optab, TFmode, SFmode, "_q_stoq");
      set_conv_libfunc (sext_optab, TFmode, DFmode, "_q_dtoq");
      set_conv_libfunc (trunc_optab, SFmode, TFmode, "_q_qtos");
      set_conv_libfunc (trunc_optab, DFmode, TFmode, "_q_qtod");
      set_conv_libfunc (sfix_optab, SImode, TFmode, "_q_qtoi");
      set_conv_libfunc (ufix_optab, SImode, TFmode, "_q_qtou");
      set_conv_libfunc (sfloat_optab, TFmode, SImode, "_q_itoq");
      set_conv_libfunc (ufloat_optab, TFmode, SImode, "_q_utoq");
    }
}