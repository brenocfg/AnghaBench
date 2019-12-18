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

__attribute__((used)) static void do_vertical_columns(float *buffer, int width, int height,
                                int column_begin, int column_end, int steps,
                                float nu, float boundaryscale, int column_step)
{
    const int numpixels = width * height;
    int i, x, k, step;
    float *ptr;
    for (x = column_begin; x < column_end;) {
        for (step = 0; step < steps; step++) {
            ptr = buffer + x;
            for (k = 0; k < column_step; k++) {
                ptr[k] *= boundaryscale;
            }
            /* Filter downwards */
            for (i = width; i < numpixels; i += width) {
                for (k = 0; k < column_step; k++) {
                    ptr[i + k] += nu * ptr[i - width + k];
                }
            }
            i = numpixels - width;

            for (k = 0; k < column_step; k++)
                ptr[i + k] *= boundaryscale;

            /* Filter upwards */
            for (; i > 0; i -= width) {
                for (k = 0; k < column_step; k++)
                    ptr[i - width + k] += nu * ptr[i + k];
            }
        }
        x += column_step;
    }
}