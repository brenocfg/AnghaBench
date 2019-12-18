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

__attribute__((used)) static void horiz_slice_c(float *buffer, int width, int height, int steps,
                          float nu, float bscale)
{
    int step, x, y;
    float *ptr;
    for (y = 0; y < height; y++) {
        for (step = 0; step < steps; step++) {
            ptr = buffer + width * y;
            ptr[0] *= bscale;

            /* Filter rightwards */
            for (x = 1; x < width; x++)
                ptr[x] += nu * ptr[x - 1];
            ptr[x = width - 1] *= bscale;

            /* Filter leftwards */
            for (; x > 0; x--)
                ptr[x - 1] += nu * ptr[x];
        }
    }
}