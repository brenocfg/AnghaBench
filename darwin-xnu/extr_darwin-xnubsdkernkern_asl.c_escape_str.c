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
 int ENOSPC ; 

int
escape_str(char *str, int len, int buflen)
{
	int count;
	char *src, *dst;

	/* Count number of characters to escape */
	src = str;
	count = 0;
	do {
		if ((*src == '[') || (*src == ']')) {
			count++;
		}
	} while (*src++);

	if (count) {
		/*
		 * Check if the buffer has enough space to escape all
		 * characters
		 */
		if ((buflen - len) < count) {
			return (ENOSPC);
		}

		src = str + len;
		dst = src + count;
		while (count) {
			*dst-- = *src;
			if ((*src == '[') || (*src == ']')) {
				/* Last char copied needs to be escaped */
				*dst-- = '\\';
				count--;
			}
			src--;
		}
	}

	return (0);
}