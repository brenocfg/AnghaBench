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
 scalar_t__ __get_user (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void show_code(unsigned int *pc)
{
	long i;

	printk("\nCode:");

	for(i = -3 ; i < 6 ; i++) {
		unsigned long insn;
		if (__get_user(insn, pc + i)) {
			printk(" (Bad address in pc)\n");
			break;
		}
		printk("%c%08lx%c",(i?' ':'<'),insn,(i?' ':'>'));
	}
}