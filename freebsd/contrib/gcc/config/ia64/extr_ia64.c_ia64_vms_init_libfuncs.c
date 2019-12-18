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
 int /*<<< orphan*/  sdiv_optab ; 
 int /*<<< orphan*/  set_optab_libfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smod_optab ; 
 int /*<<< orphan*/  udiv_optab ; 
 int /*<<< orphan*/  umod_optab ; 

__attribute__((used)) static void
ia64_vms_init_libfuncs (void)
{
  set_optab_libfunc (sdiv_optab, SImode, "OTS$DIV_I");
  set_optab_libfunc (sdiv_optab, DImode, "OTS$DIV_L");
  set_optab_libfunc (udiv_optab, SImode, "OTS$DIV_UI");
  set_optab_libfunc (udiv_optab, DImode, "OTS$DIV_UL");
  set_optab_libfunc (smod_optab, SImode, "OTS$REM_I");
  set_optab_libfunc (smod_optab, DImode, "OTS$REM_L");
  set_optab_libfunc (umod_optab, SImode, "OTS$REM_UI");
  set_optab_libfunc (umod_optab, DImode, "OTS$REM_UL");
}