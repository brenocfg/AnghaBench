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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_pal_entry(const void *a, const void *b)
{
    const int c1 = *(const uint32_t *)a & 0xffffff;
    const int c2 = *(const uint32_t *)b & 0xffffff;
    return c1 - c2;
}