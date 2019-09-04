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
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void compute_histogram16(const uint16_t *src, ptrdiff_t linesize,
                                int w, int h, float *histogram, size_t hsize)
{
    int y, x;

    memset(histogram, 0, hsize * sizeof(*histogram));

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            histogram[src[x]] += 1;
        }
        src += linesize;
    }

    for (x = 0; x < hsize - 1; x++) {
        histogram[x + 1] += histogram[x];
        histogram[x] /= hsize;
    }
    histogram[x] /= hsize;
}