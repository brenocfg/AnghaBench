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
l_strncpy(char *dest, const char *src, int len)
{
	char *stop;
	char *start;

	stop = dest + len;
	start = dest;
	while ((dest < stop) && (*src != '\0'))
		*dest++ = *src++;
	len = dest - start;
	while (dest < stop)
		*dest++ = '\0';
	return(len);
}