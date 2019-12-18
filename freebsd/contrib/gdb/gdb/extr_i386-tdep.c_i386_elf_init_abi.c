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
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i386_dwarf_reg_to_regnum ; 
 int /*<<< orphan*/  set_gdbarch_stab_reg_to_regnum (struct gdbarch*,int /*<<< orphan*/ ) ; 

void
i386_elf_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  /* We typically use stabs-in-ELF with the DWARF register numbering.  */
  set_gdbarch_stab_reg_to_regnum (gdbarch, i386_dwarf_reg_to_regnum);
}