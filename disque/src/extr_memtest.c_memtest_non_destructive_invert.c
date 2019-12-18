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

void memtest_non_destructive_invert(void *addr, size_t size) {
    volatile unsigned long *p = addr;
    size_t words = size / sizeof(unsigned long);
    size_t j;

    /* Invert */
    for (j = 0; j < words; j++)
        p[j] = ~p[j];
}