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
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *clean(char *p) {
    assert(*p == '/');
    char buf[PATH_MAX];
    char *q = buf;
    *q++ = '/';
    for (;;) {
        if (*p == '/') {
            p++;
            continue;
        }
        if (!memcmp("./", p, 2)) {
            p += 2;
            continue;
        }
        if (!memcmp("../", p, 3)) {
            p += 3;
            if (q == buf + 1)
                continue;
            for (q--; q[-1] != '/'; q--);
            continue;
        }
        while (*p != '/' && *p != '\0')
            *q++ = *p++;
        if (*p == '/') {
            *q++ = *p++;
            continue;
        }
        *q = '\0';
        return strdup(buf);
    }
}