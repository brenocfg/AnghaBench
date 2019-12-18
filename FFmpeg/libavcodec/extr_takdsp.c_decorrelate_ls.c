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
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static void decorrelate_ls(int32_t *p1, int32_t *p2, int length)
{
    int i;

    for (i = 0; i < length; i++) {
        int32_t a = p1[i];
        int32_t b = p2[i];
        p2[i]     = a + b;
    }
}