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

__attribute__((used)) static inline void copyv(const float *p1, const int stride1, float *p2, const int length)
{
    int i;

    for (i = 0; i < length; i++) {
        p2[i] = *p1;
        p1 += stride1;
    }
}