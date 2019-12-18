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
struct pt_regs {int bpc; } ;
typedef  int /*<<< orphan*/  code ;

/* Variables and functions */
 int /*<<< orphan*/  access_process_vm (int /*<<< orphan*/ ,unsigned long,unsigned long*,int,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  invalidate_cache () ; 
 scalar_t__ unregister_debug_trap (int /*<<< orphan*/ ,unsigned long,unsigned long*) ; 

void
withdraw_debug_trap(struct pt_regs *regs)
{
	unsigned long addr;
	unsigned long code;

 	addr = (regs->bpc - 2) & ~3;
	regs->bpc -= 2;
	if (unregister_debug_trap(current, addr, &code)) {
	    access_process_vm(current, addr, &code, sizeof(code), 1);
	    invalidate_cache();
	}
}