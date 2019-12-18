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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 char const* strstr (char const*,char const*) ; 

const char *
kxld_strstr(const char *s, const char *find)
{
#if KERNEL
    char c, sc;
    size_t len;
    if (!s || !find)
        return s;
    if ((c = *find++) != 0) {
        len = strlen(find);
        do {
            do {
                if ((sc = *s++) == 0)
                    return (NULL);
            } while (sc != c);
        } while (strncmp(s, find, len) != 0);
        s--;
    }
    return s;
#else
    return strstr(s, find);
#endif /* KERNEL */
}