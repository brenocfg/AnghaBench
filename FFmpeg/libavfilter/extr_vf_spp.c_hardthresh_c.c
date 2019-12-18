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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hardthresh_c(int16_t dst[64], const int16_t src[64],
                         int qp, const uint8_t *permutation)
{
    int i;
    int bias = 0; // FIXME

    unsigned threshold1 = qp * ((1<<4) - bias) - 1;
    unsigned threshold2 = threshold1 << 1;

    memset(dst, 0, 64 * sizeof(dst[0]));
    dst[0] = (src[0] + 4) >> 3;

    for (i = 1; i < 64; i++) {
        int level = src[i];
        if (((unsigned)(level + threshold1)) > threshold2) {
            const int j = permutation[i];
            dst[j] = (level + 4) >> 3;
        }
    }
}