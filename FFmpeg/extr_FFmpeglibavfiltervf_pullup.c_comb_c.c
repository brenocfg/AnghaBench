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
 scalar_t__ ABS (int const) ; 

__attribute__((used)) static int comb_c(const uint8_t *a, const uint8_t *b, ptrdiff_t s)
{
    int i, j, comb = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++)
            comb += ABS((a[j] << 1) - b[j - s] - b[j    ]) +
                    ABS((b[j] << 1) - a[j    ] - a[j + s]);
        a += s;
        b += s;
    }

    return comb;
}