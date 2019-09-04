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
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  av_strncasecmp (char const*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

int av_match_name(const char *name, const char *names)
{
    const char *p;
    int len, namelen;

    if (!name || !names)
        return 0;

    namelen = strlen(name);
    while (*names) {
        int negate = '-' == *names;
        p = strchr(names, ',');
        if (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        if (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            return !negate;
        names = p + (*p == ',');
    }
    return 0;
}