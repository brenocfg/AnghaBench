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
 int const ROW_SHIFT ; 

__attribute__((used)) static int idct_row(short *in, const int *const tab, int rnd)
{
    const int c1 = tab[0];
    const int c2 = tab[1];
    const int c3 = tab[2];
    const int c4 = tab[3];
    const int c5 = tab[4];
    const int c6 = tab[5];
    const int c7 = tab[6];

    const int right = in[5] | in[6] | in[7];
    const int left  = in[1] | in[2] | in[3];
    if (!(right | in[4])) {
        const int k = c4 * in[0] + rnd;
        if (left) {
            const int a0 = k + c2 * in[2];
            const int a1 = k + c6 * in[2];
            const int a2 = k - c6 * in[2];
            const int a3 = k - c2 * in[2];

            const int b0 = c1 * in[1] + c3 * in[3];
            const int b1 = c3 * in[1] - c7 * in[3];
            const int b2 = c5 * in[1] - c1 * in[3];
            const int b3 = c7 * in[1] - c5 * in[3];

            in[0] = (a0 + b0) >> ROW_SHIFT;
            in[1] = (a1 + b1) >> ROW_SHIFT;
            in[2] = (a2 + b2) >> ROW_SHIFT;
            in[3] = (a3 + b3) >> ROW_SHIFT;
            in[4] = (a3 - b3) >> ROW_SHIFT;
            in[5] = (a2 - b2) >> ROW_SHIFT;
            in[6] = (a1 - b1) >> ROW_SHIFT;
            in[7] = (a0 - b0) >> ROW_SHIFT;
        } else {
            const int a0 = k >> ROW_SHIFT;
            if (a0) {
                in[0] =
                in[1] =
                in[2] =
                in[3] =
                in[4] =
                in[5] =
                in[6] =
                in[7] = a0;
            } else
                return 0;
        }
    } else if (!(left | right)) {
        const int a0 = (rnd + c4 * (in[0] + in[4])) >> ROW_SHIFT;
        const int a1 = (rnd + c4 * (in[0] - in[4])) >> ROW_SHIFT;

        in[0] = a0;
        in[3] = a0;
        in[4] = a0;
        in[7] = a0;
        in[1] = a1;
        in[2] = a1;
        in[5] = a1;
        in[6] = a1;
    } else {
        const int k  = c4 * in[0] + rnd;
        const int a0 = k + c2 * in[2] + c4 * in[4] + c6 * in[6];
        const int a1 = k + c6 * in[2] - c4 * in[4] - c2 * in[6];
        const int a2 = k - c6 * in[2] - c4 * in[4] + c2 * in[6];
        const int a3 = k - c2 * in[2] + c4 * in[4] - c6 * in[6];

        const int b0 = c1 * in[1] + c3 * in[3] + c5 * in[5] + c7 * in[7];
        const int b1 = c3 * in[1] - c7 * in[3] - c1 * in[5] - c5 * in[7];
        const int b2 = c5 * in[1] - c1 * in[3] + c7 * in[5] + c3 * in[7];
        const int b3 = c7 * in[1] - c5 * in[3] + c3 * in[5] - c1 * in[7];

        in[0] = (a0 + b0) >> ROW_SHIFT;
        in[1] = (a1 + b1) >> ROW_SHIFT;
        in[2] = (a2 + b2) >> ROW_SHIFT;
        in[3] = (a3 + b3) >> ROW_SHIFT;
        in[4] = (a3 - b3) >> ROW_SHIFT;
        in[5] = (a2 - b2) >> ROW_SHIFT;
        in[6] = (a1 - b1) >> ROW_SHIFT;
        in[7] = (a0 - b0) >> ROW_SHIFT;
    }
    return 1;
}