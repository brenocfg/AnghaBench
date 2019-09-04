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

char *
strncpy(
	char *s1, 
	const char *s2,
	size_t n)
{
        char *os1 = s1;
        unsigned long i;

        for (i = 0; i < n;)
                if ((*s1++ = *s2++) == '\0')
                        for (i++; i < n; i++)
                                *s1++ = '\0';
                else
                        i++;
        return (os1);
}