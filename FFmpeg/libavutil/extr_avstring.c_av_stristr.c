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
 scalar_t__ av_stristart (char const*,char const*,int /*<<< orphan*/ *) ; 

char *av_stristr(const char *s1, const char *s2)
{
    if (!*s2)
        return (char*)(intptr_t)s1;

    do
        if (av_stristart(s1, s2, NULL))
            return (char*)(intptr_t)s1;
    while (*s1++);

    return NULL;
}