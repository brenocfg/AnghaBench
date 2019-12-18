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
 scalar_t__ MCOUNT_INSN_SIZE ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,scalar_t__) ; 

int ftrace_modify_code(unsigned long pc, unsigned char *old_code,
		       unsigned char *new_code)
{
	unsigned long err = 0, replaced = 0, old, new;

	old = *(unsigned long *)old_code;
	new = *(unsigned long *)new_code;

	__asm__ __volatile__ (
		"1:  ldr    %1, [%2]  \n"
		"    cmp    %1, %4    \n"
		"2:  streq  %3, [%2]  \n"
		"    cmpne  %1, %3    \n"
		"    movne  %0, #2    \n"
		"3:\n"

		".section .fixup, \"ax\"\n"
		"4:  mov  %0, #1  \n"
		"    b    3b      \n"
		".previous\n"

		".section __ex_table, \"a\"\n"
		"    .long 1b, 4b \n"
		"    .long 2b, 4b \n"
		".previous\n"

		: "=r"(err), "=r"(replaced)
		: "r"(pc), "r"(new), "r"(old), "0"(err), "1"(replaced)
		: "memory");

	if (!err && (replaced == old))
		flush_icache_range(pc, pc + MCOUNT_INSN_SIZE);

	return err;
}