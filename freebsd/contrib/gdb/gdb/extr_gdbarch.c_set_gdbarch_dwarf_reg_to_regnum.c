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
struct gdbarch {int /*<<< orphan*/  dwarf_reg_to_regnum; } ;
typedef  int /*<<< orphan*/  gdbarch_dwarf_reg_to_regnum_ftype ;

/* Variables and functions */

void
set_gdbarch_dwarf_reg_to_regnum (struct gdbarch *gdbarch,
                                 gdbarch_dwarf_reg_to_regnum_ftype dwarf_reg_to_regnum)
{
  gdbarch->dwarf_reg_to_regnum = dwarf_reg_to_regnum;
}