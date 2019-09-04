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

int 
bcmp(
     const void *pa,
     const void *pb,
     size_t len)
{
	const char     *a = (const char *) pa;
	const char     *b = (const char *) pb;

	if (len == 0)
		return 0;

	do
		if (*a++ != *b++)
			break;
	while (--len);

	/*
	 * Check for the overflow case but continue to handle the non-overflow
	 * case the same way just in case someone is using the return value
	 * as more than zero/non-zero
	 */
	if ((len & 0xFFFFFFFF00000000ULL) && !(len & 0x00000000FFFFFFFFULL))
		return 0xFFFFFFFFL;
	else
		return (int)len;
}