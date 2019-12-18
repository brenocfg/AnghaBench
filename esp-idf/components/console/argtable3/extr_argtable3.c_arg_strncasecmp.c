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
 int tolower (unsigned char const) ; 

__attribute__((used)) static int arg_strncasecmp(const char *s1, const char *s2, size_t n)
{
    if (n != 0)
    {
        const unsigned char *us1 = (const unsigned char *)s1;
        const unsigned char *us2 = (const unsigned char *)s2;
        do
        {
            if (tolower(*us1) != tolower(*us2++))
                return tolower(*us1) - tolower(*--us2);

            if (*us1++ == '\0')
                break;
        } while (--n != 0);
    }

    return 0;
}