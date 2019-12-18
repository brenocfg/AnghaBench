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
typedef  size_t uint32_t ;
struct bsdar {int s_cnt; char* s_sn; int s_sn_sz; scalar_t__* s_so; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_data (struct bsdar*,struct archive*,long*,int) ; 

__attribute__((used)) static void
write_bsd_symtab_entry(struct bsdar *bsdar, struct archive *a)
{
	long br_sz, br_off, br_strx;
	char *s;
	uint32_t i;

	/*
	 * Write out the size in the byte of the array of 'ranlib'
	 * descriptors to follow.
	 */

	br_sz = (long) (bsdar->s_cnt * 2 * sizeof(long));
	write_data(bsdar, a, &br_sz, sizeof(long));

	/*
	 * Write out the array of 'ranlib' descriptors.  Each
	 * descriptor comprises of (a) an offset into the following
	 * string table and (b) a file offset to the relevant member.
	 */
	for (i = 0, s = bsdar->s_sn; i < bsdar->s_cnt; i++) {
		br_strx = (long) (s - bsdar->s_sn);
		br_off = (long) bsdar->s_so[i];
		write_data(bsdar, a, &br_strx, sizeof(long));
		write_data(bsdar, a, &br_off, sizeof(long));

		/* Find the start of the next symbol in the string table. */
		while (*s++ != '\0')
			;
	}

	/*
	 * Write out the size of the string table as a 'long',
	 * followed by the string table itself.
	 */
	br_sz = (long) bsdar->s_sn_sz;
	write_data(bsdar, a, &br_sz, sizeof(long));
	write_data(bsdar, a, bsdar->s_sn, bsdar->s_sn_sz);
}