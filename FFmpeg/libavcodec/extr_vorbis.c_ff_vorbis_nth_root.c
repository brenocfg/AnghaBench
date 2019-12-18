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

unsigned int ff_vorbis_nth_root(unsigned int x, unsigned int n)
{
    unsigned int ret = 0, i, j;

    do {
        ++ret;
        for (i = 0, j = ret; i < n - 1; i++)
            j *= ret;
    } while (j <= x);

    return ret - 1;
}