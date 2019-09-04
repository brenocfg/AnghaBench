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
struct TYPE_3__ {int fbw_channels; int* start_freq; int* end_freq; scalar_t__** fixed_coeffs; int /*<<< orphan*/ ** bap; scalar_t__* channel_in_cpl; int /*<<< orphan*/ * dither_flag; } ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 size_t CPL_CH ; 

__attribute__((used)) static void remove_dithering(AC3DecodeContext *s) {
    int ch, i;

    for (ch = 1; ch <= s->fbw_channels; ch++) {
        if (!s->dither_flag[ch] && s->channel_in_cpl[ch]) {
            for (i = s->start_freq[CPL_CH]; i < s->end_freq[CPL_CH]; i++) {
                if (!s->bap[CPL_CH][i])
                    s->fixed_coeffs[ch][i] = 0;
            }
        }
    }
}