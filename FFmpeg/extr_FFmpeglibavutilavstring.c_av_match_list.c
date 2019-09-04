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
 char* strchr (char const*,char) ; 

int av_match_list(const char *name, const char *list, char separator)
{
    const char *p, *q;

    for (p = name; p && *p; ) {
        for (q = list; q && *q; ) {
            int k;
            for (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                if (k && (!p[k] || p[k] == separator))
                    return 1;
            q = strchr(q, separator);
            q += !!q;
        }
        p = strchr(p, separator);
        p += !!p;
    }

    return 0;
}