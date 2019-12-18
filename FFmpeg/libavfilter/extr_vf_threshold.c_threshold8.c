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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void threshold8(const uint8_t *in, const uint8_t *threshold,
                       const uint8_t *min, const uint8_t *max,
                       uint8_t *out,
                       ptrdiff_t ilinesize, ptrdiff_t tlinesize,
                       ptrdiff_t flinesize, ptrdiff_t slinesize,
                       ptrdiff_t olinesize,
                       int w, int h)
{
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            out[x] = in[x] < threshold[x] ? min[x] : max[x];
        }

        in        += ilinesize;
        threshold += tlinesize;
        min       += flinesize;
        max       += slinesize;
        out       += olinesize;
    }
}