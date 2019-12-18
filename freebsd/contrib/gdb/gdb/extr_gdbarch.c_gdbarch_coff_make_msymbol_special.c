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
struct minimal_symbol {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* coff_make_msymbol_special ) (int,struct minimal_symbol*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (int,struct minimal_symbol*) ; 

void
gdbarch_coff_make_msymbol_special (struct gdbarch *gdbarch, int val, struct minimal_symbol *msym)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->coff_make_msymbol_special != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_coff_make_msymbol_special called\n");
  gdbarch->coff_make_msymbol_special (val, msym);
}