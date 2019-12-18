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
 unsigned char const BUILTIN_SPECIAL ; 
 unsigned char* builtincmd ; 
 scalar_t__ memcmp (unsigned char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int
find_builtin(const char *name, int *special)
{
	const unsigned char *bp;
	size_t len;

	len = strlen(name);
	for (bp = builtincmd ; *bp ; bp += 2 + bp[0]) {
		if (bp[0] == len && memcmp(bp + 2, name, len) == 0) {
			*special = (bp[1] & BUILTIN_SPECIAL) != 0;
			return bp[1] & ~BUILTIN_SPECIAL;
		}
	}
	return -1;
}