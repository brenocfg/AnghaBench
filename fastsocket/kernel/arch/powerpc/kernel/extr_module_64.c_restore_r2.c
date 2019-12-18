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
typedef  int u32 ;
struct module {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int PPC_INST_NOP ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int restore_r2(u32 *instruction, struct module *me)
{
	if (*instruction != PPC_INST_NOP) {
		printk("%s: Expect noop after relocate, got %08x\n",
		       me->name, *instruction);
		return 0;
	}
	*instruction = 0xe8410028;	/* ld r2,40(r1) */
	return 1;
}