#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMREGBYTES ; 
 int /*<<< orphan*/  eprintk (char*,int,unsigned long) ; 
 int /*<<< orphan*/  gdb_regs_to_pt_regs (scalar_t__,TYPE_1__*) ; 
 int instruction_pointer (TYPE_1__*) ; 
 int /*<<< orphan*/  kgdb_hex2mem (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kgdbts_gdb_regs ; 
 TYPE_1__ kgdbts_regs ; 
 unsigned long lookup_addr (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  v2printk (char*,int) ; 

__attribute__((used)) static int check_and_rewind_pc(char *put_str, char *arg)
{
	unsigned long addr = lookup_addr(arg);
	int offset = 0;

	kgdb_hex2mem(&put_str[1], (char *)kgdbts_gdb_regs,
		 NUMREGBYTES);
	gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
	v2printk("Stopped at IP: %lx\n", instruction_pointer(&kgdbts_regs));
#ifdef CONFIG_X86
	/* On x86 a breakpoint stop requires it to be decremented */
	if (addr + 1 == kgdbts_regs.ip)
		offset = -1;
#endif
	if (strcmp(arg, "silent") &&
		instruction_pointer(&kgdbts_regs) + offset != addr) {
		eprintk("kgdbts: BP mismatch %lx expected %lx\n",
			   instruction_pointer(&kgdbts_regs) + offset, addr);
		return 1;
	}
#ifdef CONFIG_X86
	/* On x86 adjust the instruction pointer if needed */
	kgdbts_regs.ip += offset;
#endif
	return 0;
}