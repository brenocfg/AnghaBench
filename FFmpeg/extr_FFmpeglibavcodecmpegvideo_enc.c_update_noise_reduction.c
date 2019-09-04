#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* dct_count; int** dct_error_sum; int** dct_offset; int noise_reduction; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static void update_noise_reduction(MpegEncContext *s)
{
    int intra, i;

    for (intra = 0; intra < 2; intra++) {
        if (s->dct_count[intra] > (1 << 16)) {
            for (i = 0; i < 64; i++) {
                s->dct_error_sum[intra][i] >>= 1;
            }
            s->dct_count[intra] >>= 1;
        }

        for (i = 0; i < 64; i++) {
            s->dct_offset[intra][i] = (s->noise_reduction *
                                       s->dct_count[intra] +
                                       s->dct_error_sum[intra][i] / 2) /
                                      (s->dct_error_sum[intra][i] + 1);
        }
    }
}