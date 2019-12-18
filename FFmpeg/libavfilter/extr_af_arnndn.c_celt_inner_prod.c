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

__attribute__((used)) static inline float celt_inner_prod(const float *x,
                                    const float *y, int N)
{
    float xy = 0.f;

    for (int i = 0; i < N; i++)
        xy += x[i] * y[i];

    return xy;
}