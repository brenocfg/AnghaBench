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

void ff_tilt_compensation(float *mem, float tilt, float *samples, int size)
{
    float new_tilt_mem = samples[size - 1];
    int i;

    for (i = size - 1; i > 0; i--)
        samples[i] -= tilt * samples[i - 1];

    samples[0] -= tilt * *mem;
    *mem = new_tilt_mem;
}