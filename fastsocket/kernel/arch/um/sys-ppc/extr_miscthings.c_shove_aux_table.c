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
 unsigned long AT_NULL ; 

void shove_aux_table(unsigned long sp)
{
	int argc;
	char *p;
	unsigned long e;
	unsigned long aux_start, offset;

	argc = *(int *)sp;
	sp += sizeof(int) + (argc + 1) * sizeof(char *);
	/* skip over the environment pointers */
	do {
		p = *(char **)sp;
		sp += sizeof(char *);
	} while (p != NULL);
	aux_start = sp;
	/* skip to the end of the auxiliary table */
	do {
		e = *(unsigned long *)sp;
		sp += 2 * sizeof(unsigned long);
	} while (e != AT_NULL);
	offset = ((aux_start + 15) & ~15) - aux_start;
	if (offset != 0) {
		do {
			sp -= sizeof(unsigned long);
			e = *(unsigned long *)sp;
			*(unsigned long *)(sp + offset) = e;
		} while (sp > aux_start);
	}
}