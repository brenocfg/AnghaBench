#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  gdb_bpt_instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_INSTR_SIZE ; 
 TYPE_1__ arch_kgdb_ops ; 
 int bfin_probe_kernel_read (char*,char*,int /*<<< orphan*/ ) ; 
 int bfin_probe_kernel_write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kgdb_arch_set_breakpoint(unsigned long addr, char *saved_instr)
{
	int err = bfin_probe_kernel_read(saved_instr, (char *)addr,
	                                 BREAK_INSTR_SIZE);
	if (err)
		return err;
	return bfin_probe_kernel_write((char *)addr, arch_kgdb_ops.gdb_bpt_instr,
	                               BREAK_INSTR_SIZE);
}