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
typedef  int u16 ;
struct branch {int opcode; unsigned long delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

unsigned paravirt_patch_call(void *insnbuf,
			     const void *target, u16 tgt_clobbers,
			     unsigned long addr, u16 site_clobbers,
			     unsigned len)
{
	struct branch *b = insnbuf;
	unsigned long delta = (unsigned long)target - (addr+5);

	if (tgt_clobbers & ~site_clobbers)
		return len;	/* target would clobber too much for this site */
	if (len < 5)
		return len;	/* call too long for patch site */

	b->opcode = 0xe8; /* call */
	b->delta = delta;
	BUILD_BUG_ON(sizeof(*b) != 5);

	return 5;
}