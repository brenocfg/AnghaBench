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

int ff_fmt_is_in(int fmt, const int *fmts)
{
    const int *p;

    for (p = fmts; *p != -1; p++) {
        if (fmt == *p)
            return 1;
    }
    return 0;
}