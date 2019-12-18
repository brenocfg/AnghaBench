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
struct gdbarch {int /*<<< orphan*/  stab_reg_to_regnum; } ;
typedef  int /*<<< orphan*/  gdbarch_stab_reg_to_regnum_ftype ;

/* Variables and functions */

void
set_gdbarch_stab_reg_to_regnum (struct gdbarch *gdbarch,
                                gdbarch_stab_reg_to_regnum_ftype stab_reg_to_regnum)
{
  gdbarch->stab_reg_to_regnum = stab_reg_to_regnum;
}