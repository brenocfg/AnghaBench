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
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TFmode ; 
 int /*<<< orphan*/  abs_optab ; 
 int /*<<< orphan*/  cmptf_libfunc ; 
 int /*<<< orphan*/  eq_optab ; 
 int /*<<< orphan*/  ge_optab ; 
 int /*<<< orphan*/  gt_optab ; 
 int /*<<< orphan*/  ia64_init_libfuncs () ; 
 int /*<<< orphan*/  init_one_libfunc (char*) ; 
 int /*<<< orphan*/  le_optab ; 
 int /*<<< orphan*/  lt_optab ; 
 int /*<<< orphan*/  ne_optab ; 
 int /*<<< orphan*/  sdiv_optab ; 
 int /*<<< orphan*/  set_optab_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smax_optab ; 
 int /*<<< orphan*/  smin_optab ; 
 int /*<<< orphan*/  smod_optab ; 
 int /*<<< orphan*/  udiv_optab ; 
 int /*<<< orphan*/  umod_optab ; 

__attribute__((used)) static void
ia64_hpux_init_libfuncs (void)
{
  ia64_init_libfuncs ();

  /* The HP SI millicode division and mod functions expect DI arguments.
     By turning them off completely we avoid using both libgcc and the
     non-standard millicode routines and use the HP DI millicode routines
     instead.  */

  set_optab_libfunc (sdiv_optab, SImode, 0);
  set_optab_libfunc (udiv_optab, SImode, 0);
  set_optab_libfunc (smod_optab, SImode, 0);
  set_optab_libfunc (umod_optab, SImode, 0);

  set_optab_libfunc (sdiv_optab, DImode, "__milli_divI");
  set_optab_libfunc (udiv_optab, DImode, "__milli_divU");
  set_optab_libfunc (smod_optab, DImode, "__milli_remI");
  set_optab_libfunc (umod_optab, DImode, "__milli_remU");

  /* HP-UX libc has TF min/max/abs routines in it.  */
  set_optab_libfunc (smin_optab, TFmode, "_U_Qfmin");
  set_optab_libfunc (smax_optab, TFmode, "_U_Qfmax");
  set_optab_libfunc (abs_optab, TFmode, "_U_Qfabs");

  /* ia64_expand_compare uses this.  */
  cmptf_libfunc = init_one_libfunc ("_U_Qfcmp");

  /* These should never be used.  */
  set_optab_libfunc (eq_optab, TFmode, 0);
  set_optab_libfunc (ne_optab, TFmode, 0);
  set_optab_libfunc (gt_optab, TFmode, 0);
  set_optab_libfunc (ge_optab, TFmode, 0);
  set_optab_libfunc (lt_optab, TFmode, 0);
  set_optab_libfunc (le_optab, TFmode, 0);
}