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
 int ARRAY_SIZE (char const*) ; 
 int EINVAL ; 

__attribute__((used)) static int csr1212_check_minimal_ascii(const char *s)
{
	static const char minimal_ascii_table[] = {
					/*  1   2   4   8  16  32  64  128 */
		128,			/* --, --, --, --, --, --, --, 07, */
		4 + 16 + 32,		/* --, --, 0a, --, 0C, 0D, --, --, */
		0,			/* --, --, --, --, --, --, --, --, */
		0,			/* --, --, --, --, --, --, --, --, */
		255 - 8 - 16,		/* 20, 21, 22, --, --, 25, 26, 27, */
		255,			/* 28, 29, 2a, 2b, 2c, 2d, 2e, 2f, */
		255,			/* 30, 31, 32, 33, 34, 35, 36, 37, */
		255,			/* 38, 39, 3a, 3b, 3c, 3d, 3e, 3f, */
		255,			/* 40, 41, 42, 43, 44, 45, 46, 47, */
		255,			/* 48, 49, 4a, 4b, 4c, 4d, 4e, 4f, */
		255,			/* 50, 51, 52, 53, 54, 55, 56, 57, */
		1 + 2 + 4 + 128,	/* 58, 59, 5a, --, --, --, --, 5f, */
		255 - 1,		/* --, 61, 62, 63, 64, 65, 66, 67, */
		255,			/* 68, 69, 6a, 6b, 6c, 6d, 6e, 6f, */
		255,			/* 70, 71, 72, 73, 74, 75, 76, 77, */
		1 + 2 + 4,		/* 78, 79, 7a, --, --, --, --, --, */
	};
	int i, j;

	for (; *s; s++) {
		i = *s >> 3;		/*  i = *s / 8;		*/
		j = 1 << (*s & 3);	/*  j = 1 << (*s % 8);	*/

		if (i >= ARRAY_SIZE(minimal_ascii_table) ||
		    !(minimal_ascii_table[i] & j))
			return -EINVAL;
	}
	return 0;
}