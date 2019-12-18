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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void threshold16(const uint8_t *iin, const uint8_t *tthreshold,
                        const uint8_t *ffirst, const uint8_t *ssecond,
                        uint8_t *oout,
                        ptrdiff_t ilinesize, ptrdiff_t tlinesize,
                        ptrdiff_t flinesize, ptrdiff_t slinesize,
                        ptrdiff_t olinesize,
                        int w, int h)
{
    const uint16_t *in = (const uint16_t *)iin;
    const uint16_t *threshold = (const uint16_t *)tthreshold;
    const uint16_t *min = (const uint16_t *)ffirst;
    const uint16_t *max = (const uint16_t *)ssecond;
    uint16_t *out = (uint16_t *)oout;
    int x, y;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            out[x] = in[x] < threshold[x] ? min[x] : max[x];
        }

        in        += ilinesize / 2;
        threshold += tlinesize / 2;
        min       += flinesize / 2;
        max       += slinesize / 2;
        out       += olinesize / 2;
    }
}