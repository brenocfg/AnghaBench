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
typedef  unsigned int uint64_t ;
typedef  unsigned int uint16_t ;
typedef  int ptrdiff_t ;
typedef  unsigned int int64_t ;

/* Variables and functions */

__attribute__((used)) static void ssim_4x4xn_16bit(const uint8_t *main8, ptrdiff_t main_stride,
                             const uint8_t *ref8, ptrdiff_t ref_stride,
                             int64_t (*sums)[4], int width)
{
    const uint16_t *main16 = (const uint16_t *)main8;
    const uint16_t *ref16  = (const uint16_t *)ref8;
    int x, y, z;

    main_stride >>= 1;
    ref_stride >>= 1;

    for (z = 0; z < width; z++) {
        uint64_t s1 = 0, s2 = 0, ss = 0, s12 = 0;

        for (y = 0; y < 4; y++) {
            for (x = 0; x < 4; x++) {
                unsigned a = main16[x + y * main_stride];
                unsigned b = ref16[x + y * ref_stride];

                s1  += a;
                s2  += b;
                ss  += a*a;
                ss  += b*b;
                s12 += a*b;
            }
        }

        sums[z][0] = s1;
        sums[z][1] = s2;
        sums[z][2] = ss;
        sums[z][3] = s12;
        main16 += 4;
        ref16 += 4;
    }
}