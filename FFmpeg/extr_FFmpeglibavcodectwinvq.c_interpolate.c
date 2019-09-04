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

__attribute__((used)) static void interpolate(float *out, float v1, float v2, int size)
{
    int i;
    float step = (v1 - v2) / (size + 1);

    for (i = 0; i < size; i++) {
        v2    += step;
        out[i] = v2;
    }
}