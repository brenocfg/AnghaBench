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
 size_t strlen (char*) ; 

size_t
strlcpy(char *dst, const char *src, size_t len)
{
	size_t ret = strlen(dst);

	while (len > 1) {
		*dst++ = *src++;
		len--;
	}
	if (len > 0)
		*dst = '\0';
	return (ret);
}