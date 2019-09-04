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
typedef  int uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int lrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgtc1_block_internal (int*,int,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqrtf (int) ; 

__attribute__((used)) static inline void rgtc2_block_internal(uint8_t *dst, ptrdiff_t stride,
                                        const uint8_t *block, int sign)
{
    /* 4x4 block containing 4 component pixels. */
    uint8_t c0[4 * 4 * 4];
    uint8_t c1[4 * 4 * 4];
    int x, y;

    /* Decompress the two channels separately and interleave them afterwards. */
    rgtc1_block_internal(c0, 16, block, sign, 0, 0, 4);
    rgtc1_block_internal(c1, 16, block + 8, sign, 0, 0, 4);

    /* B is rebuilt exactly like a normal map. */
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            uint8_t *p = dst + x * 4 + y * stride;
            int r = c0[x * 4 + y * 16];
            int g = c1[x * 4 + y * 16];
            int b = 127;

            int d = (255 * 255 - r * r - g * g) / 2;
            if (d > 0)
                b = lrint(sqrtf(d));

            p[0] = r;
            p[1] = g;
            p[2] = b;
            p[3] = 255;
        }
    }
}