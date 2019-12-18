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
struct exception_table_entry {int fixup; unsigned long insn; } ;

/* Variables and functions */

const struct exception_table_entry *
search_extable(const struct exception_table_entry *start,
	       const struct exception_table_entry *last,
	       unsigned long value)
{
	const struct exception_table_entry *walk;

	/* Single insn entries are encoded as:
	 *	word 1:	insn address
	 *	word 2:	fixup code address
	 *
	 * Range entries are encoded as:
	 *	word 1: first insn address
	 *	word 2: 0
	 *	word 3: last insn address + 4 bytes
	 *	word 4: fixup code address
	 *
	 * Deleted entries are encoded as:
	 *	word 1: unused
	 *	word 2: -1
	 *
	 * See asm/uaccess.h for more details.
	 */

	/* 1. Try to find an exact match. */
	for (walk = start; walk <= last; walk++) {
		if (walk->fixup == 0) {
			/* A range entry, skip both parts. */
			walk++;
			continue;
		}

		/* A deleted entry; see trim_init_extable */
		if (walk->fixup == -1)
			continue;

		if (walk->insn == value)
			return walk;
	}

	/* 2. Try to find a range match. */
	for (walk = start; walk <= (last - 1); walk++) {
		if (walk->fixup)
			continue;

		if (walk[0].insn <= value && walk[1].insn > value)
			return walk;

		walk++;
	}

        return NULL;
}