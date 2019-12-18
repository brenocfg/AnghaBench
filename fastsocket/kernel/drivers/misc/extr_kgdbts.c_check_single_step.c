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
 int /*<<< orphan*/  NUMREGBYTES ; 
 int /*<<< orphan*/  eprintk (char*,unsigned long) ; 
 int /*<<< orphan*/  gdb_regs_to_pt_regs (scalar_t__,int /*<<< orphan*/ *) ; 
 unsigned long instruction_pointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdb_hex2mem (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kgdbts_gdb_regs ; 
 int /*<<< orphan*/  kgdbts_regs ; 
 unsigned long lookup_addr (char*) ; 
 int /*<<< orphan*/  v2printk (char*,unsigned long) ; 

__attribute__((used)) static int check_single_step(char *put_str, char *arg)
{
	unsigned long addr = lookup_addr(arg);
	/*
	 * From an arch indepent point of view the instruction pointer
	 * should be on a different instruction
	 */
	kgdb_hex2mem(&put_str[1], (char *)kgdbts_gdb_regs,
		 NUMREGBYTES);
	gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
	v2printk("Singlestep stopped at IP: %lx\n",
		   instruction_pointer(&kgdbts_regs));
	if (instruction_pointer(&kgdbts_regs) == addr) {
		eprintk("kgdbts: SingleStep failed at %lx\n",
			   instruction_pointer(&kgdbts_regs));
		return 1;
	}

	return 0;
}