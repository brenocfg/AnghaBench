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
struct TYPE_3__ {float** coeffs; int num_windows; int num_bands; int* band_start; scalar_t__* ms_info; } ;
typedef  TYPE_1__ On2AVCContext ;

/* Variables and functions */

__attribute__((used)) static int on2avc_apply_ms(On2AVCContext *c)
{
    int w, b, i;
    int band_off = 0;
    float *ch0 = c->coeffs[0];
    float *ch1 = c->coeffs[1];

    for (w = 0; w < c->num_windows; w++) {
        for (b = 0; b < c->num_bands; b++) {
            if (c->ms_info[band_off + b]) {
                for (i = c->band_start[b]; i < c->band_start[b + 1]; i++) {
                    float l = *ch0, r = *ch1;
                    *ch0++ = l + r;
                    *ch1++ = l - r;
                }
            } else {
                ch0 += c->band_start[b + 1] - c->band_start[b];
                ch1 += c->band_start[b + 1] - c->band_start[b];
            }
        }
        band_off += c->num_bands;
    }
    return 0;
}