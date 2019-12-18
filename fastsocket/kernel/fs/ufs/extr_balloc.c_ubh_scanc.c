#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ufs_sb_private_info {unsigned int s_fmask; unsigned int s_fshift; unsigned int s_fsize; } ;
struct ufs_buffer_head {TYPE_1__** bh; } ;
struct TYPE_2__ {unsigned char* b_data; } ;

/* Variables and functions */

__attribute__((used)) static unsigned ubh_scanc(struct ufs_sb_private_info *uspi,
			  struct ufs_buffer_head *ubh,
			  unsigned begin, unsigned size,
			  unsigned char *table, unsigned char mask)
{
	unsigned rest, offset;
	unsigned char *cp;
	

	offset = begin & ~uspi->s_fmask;
	begin >>= uspi->s_fshift;
	for (;;) {
		if ((offset + size) < uspi->s_fsize)
			rest = size;
		else
			rest = uspi->s_fsize - offset;
		size -= rest;
		cp = ubh->bh[begin]->b_data + offset;
		while ((table[*cp++] & mask) == 0 && --rest)
			;
		if (rest || !size)
			break;
		begin++;
		offset = 0;
	}
	return (size + rest);
}