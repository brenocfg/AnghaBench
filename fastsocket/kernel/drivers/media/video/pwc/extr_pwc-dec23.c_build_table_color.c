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
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */

__attribute__((used)) static void build_table_color(const unsigned int romtable[16][8],
			      unsigned char p0004[16][1024],
			      unsigned char p8004[16][256])
{
	int compression_mode, j, k, bit, pw;
	unsigned char *p0, *p8;
	const unsigned int *r;

	/* We have 16 compressions tables */
	for (compression_mode = 0; compression_mode < 16; compression_mode++) {
		p0 = p0004[compression_mode];
		p8 = p8004[compression_mode];
		r  = romtable[compression_mode];

		for (j = 0; j < 8; j++, r++, p0 += 128) {

			for (k = 0; k < 16; k++) {
				if (k == 0)
					bit = 1;
				else if (k >= 1 && k < 3)
					bit = (r[0] >> 15) & 7;
				else if (k >= 3 && k < 6)
					bit = (r[0] >> 12) & 7;
				else if (k >= 6 && k < 10)
					bit = (r[0] >> 9) & 7;
				else if (k >= 10 && k < 13)
					bit = (r[0] >> 6) & 7;
				else if (k >= 13 && k < 15)
					bit = (r[0] >> 3) & 7;
				else
					bit = (r[0]) & 7;
				if (k == 0)
					*p8++ = 8;
				else
					*p8++ = j - bit;
				*p8++ = bit;

				pw = 1 << bit;
				p0[k + 0x00] = (1 * pw) + 0x80;
				p0[k + 0x10] = (2 * pw) + 0x80;
				p0[k + 0x20] = (3 * pw) + 0x80;
				p0[k + 0x30] = (4 * pw) + 0x80;
				p0[k + 0x40] = (-1 * pw) + 0x80;
				p0[k + 0x50] = (-2 * pw) + 0x80;
				p0[k + 0x60] = (-3 * pw) + 0x80;
				p0[k + 0x70] = (-4 * pw) + 0x80;
			}	/* end of for (k=0; k<16; k++, p8++) */
		}	/* end of for (j=0; j<8; j++ , table++) */
	} /* end of foreach compression_mode */
}