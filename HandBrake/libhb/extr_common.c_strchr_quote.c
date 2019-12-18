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

__attribute__((used)) static const char* strchr_quote(const char *pos, char c, char q)
{
    if (pos == NULL)
        return NULL;

    while (*pos != 0 && *pos != c)
    {
        if (*pos == q)
        {
            pos = strchr_quote(pos+1, q, 0);
            if (pos == NULL)
                return NULL;
            pos++;
        }
        else if (*pos == '\\' && *(pos+1) != 0)
            pos += 2;
        else
            pos++;
    }
    if (*pos != c)
        return NULL;
    return pos;
}