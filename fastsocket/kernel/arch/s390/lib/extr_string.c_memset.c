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
 void* __builtin_memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *memset(void *s, int c, size_t n)
{
	char *xs;

	if (c == 0)
		return __builtin_memset(s, 0, n);

	xs = (char *) s;
	if (n > 0)
		do {
			*xs++ = c;
		} while (--n > 0);
	return s;
}