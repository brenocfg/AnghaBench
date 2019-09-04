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
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static void get_lsp_poly(int16_t *lsp, int32_t *f)
{
    int16_t high, low;
    int i, j, k, l;
    int32_t tmp;

    f[0] = 16777216;
    f[1] = lsp[0] * -1024;

    for (i = 2, k = 2, l = 2; i <= 5; i++, k += 2) {
        f[l] = f[l - 2];

        for (j = i; j > 1; j--, l--) {
            high = f[l - 1] >> 16;
            low = (f[l - 1] - (high * (1 << 16))) >> 1;

            tmp = ((high * lsp[k]) * 4) + (((low * lsp[k]) >> 15) * 4);

            f[l] += f[l - 2];
            f[l] -= (unsigned)tmp;
        }

        f[l] -= lsp[k] * (1 << 10);
        l += i;
    }
}