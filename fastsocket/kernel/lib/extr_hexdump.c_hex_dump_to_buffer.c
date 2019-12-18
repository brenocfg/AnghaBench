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
typedef  char u8 ;
typedef  scalar_t__ u64 ;
typedef  unsigned long long u32 ;
typedef  unsigned long long u16 ;

/* Variables and functions */
 char hex_asc_hi (char) ; 
 char hex_asc_lo (char) ; 
 scalar_t__ isascii (char const) ; 
 scalar_t__ isprint (char const) ; 
 int scnprintf (char*,size_t,char*,char*,unsigned long long const) ; 

void hex_dump_to_buffer(const void *buf, size_t len, int rowsize,
			int groupsize, char *linebuf, size_t linebuflen,
			bool ascii)
{
	const u8 *ptr = buf;
	u8 ch;
	int j, lx = 0;
	int ascii_column;

	if (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	if (!len)
		goto nil;
	if (len > rowsize)		/* limit to one line at a time */
		len = rowsize;
	if ((len % groupsize) != 0)	/* no mixed size output */
		groupsize = 1;

	switch (groupsize) {
	case 8: {
		const u64 *ptr8 = buf;
		int ngroups = len / groupsize;

		for (j = 0; j < ngroups; j++)
			lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%s%16.16llx", j ? " " : "",
				(unsigned long long)*(ptr8 + j));
		ascii_column = 17 * ngroups + 2;
		break;
	}

	case 4: {
		const u32 *ptr4 = buf;
		int ngroups = len / groupsize;

		for (j = 0; j < ngroups; j++)
			lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%s%8.8x", j ? " " : "", *(ptr4 + j));
		ascii_column = 9 * ngroups + 2;
		break;
	}

	case 2: {
		const u16 *ptr2 = buf;
		int ngroups = len / groupsize;

		for (j = 0; j < ngroups; j++)
			lx += scnprintf(linebuf + lx, linebuflen - lx,
				"%s%4.4x", j ? " " : "", *(ptr2 + j));
		ascii_column = 5 * ngroups + 2;
		break;
	}

	default:
		for (j = 0; (j < len) && (lx + 3) <= linebuflen; j++) {
			ch = ptr[j];
			linebuf[lx++] = hex_asc_hi(ch);
			linebuf[lx++] = hex_asc_lo(ch);
			linebuf[lx++] = ' ';
		}
		if (j)
			lx--;

		ascii_column = 3 * rowsize + 2;
		break;
	}
	if (!ascii)
		goto nil;

	while (lx < (linebuflen - 1) && lx < (ascii_column - 1))
		linebuf[lx++] = ' ';
	for (j = 0; (j < len) && (lx + 2) < linebuflen; j++)
		linebuf[lx++] = (isascii(ptr[j]) && isprint(ptr[j])) ? ptr[j]
				: '.';
nil:
	linebuf[lx++] = '\0';
}