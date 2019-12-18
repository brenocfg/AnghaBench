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
struct gdbarch {int /*<<< orphan*/  (* elf_make_msymbol_special ) (int /*<<< orphan*/ *,struct minimal_symbol*) ;} ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct minimal_symbol*) ; 

void
gdbarch_elf_make_msymbol_special (struct gdbarch *gdbarch, asymbol *sym, struct minimal_symbol *msym)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->elf_make_msymbol_special != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_elf_make_msymbol_special called\n");
  gdbarch->elf_make_msymbol_special (sym, msym);
}