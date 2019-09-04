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

__attribute__((used)) static int safe_filename(const char *f)
{
    const char *start = f;

    for (; *f; f++) {
        /* A-Za-z0-9_- */
        if (!((unsigned)((*f | 32) - 'a') < 26 ||
              (unsigned)(*f - '0') < 10 || *f == '_' || *f == '-')) {
            if (f == start)
                return 0;
            else if (*f == '/')
                start = f + 1;
            else if (*f != '.')
                return 0;
        }
    }
    return 1;
}