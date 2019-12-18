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
 int BRANCH_ABSOLUTE ; 

unsigned int create_cond_branch(const unsigned int *addr,
				unsigned long target, int flags)
{
	unsigned int instruction;
	long offset;

	offset = target;
	if (! (flags & BRANCH_ABSOLUTE))
		offset = offset - (unsigned long)addr;

	/* Check we can represent the target in the instruction format */
	if (offset < -0x8000 || offset > 0x7FFF || offset & 0x3)
		return 0;

	/* Mask out the flags and target, so they don't step on each other. */
	instruction = 0x40000000 | (flags & 0x3FF0003) | (offset & 0xFFFC);

	return instruction;
}