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
 int BITS_PER_LONG ; 
 int BITS_TO_LONGS (int) ; 
#define  REG_OP_ALLOC 130 
#define  REG_OP_ISFREE 129 
#define  REG_OP_RELEASE 128 
 int min (int,int) ; 

__attribute__((used)) static int __reg_op(unsigned long *bitmap, int pos, int order, int reg_op)
{
	int nbits_reg;		/* number of bits in region */
	int index;		/* index first long of region in bitmap */
	int offset;		/* bit offset region in bitmap[index] */
	int nlongs_reg;		/* num longs spanned by region in bitmap */
	int nbitsinlong;	/* num bits of region in each spanned long */
	unsigned long mask;	/* bitmask for one long of region */
	int i;			/* scans bitmap by longs */
	int ret = 0;		/* return value */

	/*
	 * Either nlongs_reg == 1 (for small orders that fit in one long)
	 * or (offset == 0 && mask == ~0UL) (for larger multiword orders.)
	 */
	nbits_reg = 1 << order;
	index = pos / BITS_PER_LONG;
	offset = pos - (index * BITS_PER_LONG);
	nlongs_reg = BITS_TO_LONGS(nbits_reg);
	nbitsinlong = min(nbits_reg,  BITS_PER_LONG);

	/*
	 * Can't do "mask = (1UL << nbitsinlong) - 1", as that
	 * overflows if nbitsinlong == BITS_PER_LONG.
	 */
	mask = (1UL << (nbitsinlong - 1));
	mask += mask - 1;
	mask <<= offset;

	switch (reg_op) {
	case REG_OP_ISFREE:
		for (i = 0; i < nlongs_reg; i++) {
			if (bitmap[index + i] & mask)
				goto done;
		}
		ret = 1;	/* all bits in region free (zero) */
		break;

	case REG_OP_ALLOC:
		for (i = 0; i < nlongs_reg; i++)
			bitmap[index + i] |= mask;
		break;

	case REG_OP_RELEASE:
		for (i = 0; i < nlongs_reg; i++)
			bitmap[index + i] &= ~mask;
		break;
	}
done:
	return ret;
}