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

/* Variables and functions */

__attribute__((used)) static void ttaenc_filter_process_c(int32_t *qm, int32_t *dx, int32_t *dl,
                                    int32_t *error, int32_t *in, int32_t shift,
                                    int32_t round) {
    if (*error < 0) {
        qm[0] -= dx[0]; qm[1] -= dx[1]; qm[2] -= dx[2]; qm[3] -= dx[3];
        qm[4] -= dx[4]; qm[5] -= dx[5]; qm[6] -= dx[6]; qm[7] -= dx[7];
    } else if (*error > 0) {
        qm[0] += dx[0]; qm[1] += dx[1]; qm[2] += dx[2]; qm[3] += dx[3];
        qm[4] += dx[4]; qm[5] += dx[5]; qm[6] += dx[6]; qm[7] += dx[7];
    }

    round += dl[0] * qm[0] + dl[1] * qm[1] + dl[2] * qm[2] + dl[3] * qm[3] +
             dl[4] * qm[4] + dl[5] * qm[5] + dl[6] * qm[6] + dl[7] * qm[7];

    dx[0] = dx[1]; dx[1] = dx[2]; dx[2] = dx[3]; dx[3] = dx[4];
    dl[0] = dl[1]; dl[1] = dl[2]; dl[2] = dl[3]; dl[3] = dl[4];

    dx[4] = ((dl[4] >> 30) | 1);
    dx[5] = ((dl[5] >> 30) | 2) & ~1;
    dx[6] = ((dl[6] >> 30) | 2) & ~1;
    dx[7] = ((dl[7] >> 30) | 4) & ~3;

    dl[4] = -dl[5]; dl[5] = -dl[6];
    dl[6] = *in - dl[7]; dl[7] = *in;
    dl[5] += dl[6]; dl[4] += dl[5];

    *in -= (round >> shift);
    *error = *in;
}