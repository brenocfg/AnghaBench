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
 int /*<<< orphan*/  pretwiddle (float*,float*,int,int,int,int,int,double const* const*) ; 

__attribute__((used)) static void twiddle(float *src1, float *src2, int src2_len,
                    const double *tab, int tab_len, int step,
                    int order0, int order1, const double * const *tabs)
{
    int steps;
    int mask;
    int i, j;

    steps = (src2_len - tab_len) / step + 1;
    pretwiddle(src1, src2, src2_len, tab_len, step, order0, order1, tabs);
    mask = tab_len - 1;

    for (i = 0; i < steps; i++) {
        float in0 = src1[order0 + i];
        int   pos = (src2_len - 1) & mask;

        if (pos < tab_len) {
            const double *t = tab;
            for (j = pos; j >= 0; j--)
                src2[j] += in0 * *t++;
            for (j = 0; j < tab_len - pos - 1; j++)
                src2[src2_len - j - 1] += in0 * tab[pos + 1 + j];
        } else {
            for (j = 0; j < tab_len; j++)
                src2[pos - j] += in0 * tab[j];
        }
        mask = pos + step;
    }
}