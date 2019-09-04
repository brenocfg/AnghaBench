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

__attribute__((used)) static void clip_interval(int wmax, int *x, int *w, int *dx)
{
    if (dx)
        *dx = 0;
    if (*x < 0) {
        if (dx)
            *dx = -*x;
        *w += *x;
        *x = 0;
    }
    if (*x + *w > wmax)
        *w = wmax - *x;
}