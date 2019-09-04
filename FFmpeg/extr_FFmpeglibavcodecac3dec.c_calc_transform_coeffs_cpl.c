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
struct TYPE_3__ {int* start_freq; int num_cpl_bands; int* cpl_band_sizes; int fbw_channels; int** cpl_coords; int** fixed_coeffs; scalar_t__* phase_flags; scalar_t__* channel_in_cpl; } ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 size_t CPL_CH ; 
 int MULH (int,int) ; 

__attribute__((used)) static void calc_transform_coeffs_cpl(AC3DecodeContext *s)
{
    int bin, band, ch;

    bin = s->start_freq[CPL_CH];
    for (band = 0; band < s->num_cpl_bands; band++) {
        int band_start = bin;
        int band_end = bin + s->cpl_band_sizes[band];
        for (ch = 1; ch <= s->fbw_channels; ch++) {
            if (s->channel_in_cpl[ch]) {
                int cpl_coord = s->cpl_coords[ch][band] << 5;
                for (bin = band_start; bin < band_end; bin++) {
                    s->fixed_coeffs[ch][bin] =
                        MULH(s->fixed_coeffs[CPL_CH][bin] * (1 << 4), cpl_coord);
                }
                if (ch == 2 && s->phase_flags[band]) {
                    for (bin = band_start; bin < band_end; bin++)
                        s->fixed_coeffs[2][bin] = -s->fixed_coeffs[2][bin];
                }
            }
        }
        bin = band_end;
    }
}