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
mig_strncpy(
	char		*dest,
	const char	*src,
	int		len)
{
    int i = 0;

    if (len > 0)
	if (dest != NULL) {
	    if (src != NULL)
		   for (i=1; i<len; i++)
			if (! (*dest++ = *src++))
			    return i;
	        *dest = '\0';
	}
    return i;
}