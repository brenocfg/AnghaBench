#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int** masking_curve_cb; int fullband_channels; int* channel_order_tab; int** history; int channels; int* eff_masking_curve_cb; int* band_masking_cb; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int SUBSUBFRAMES ; 
 int /*<<< orphan*/  adjust_jnd (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  update_band_masking ; 
 int /*<<< orphan*/  walk_band_high (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_band_low (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void calc_masking(DCAEncContext *c, const int32_t *input)
{
    int i, k, band, ch, ssf;
    int32_t data[512];

    for (i = 0; i < 256; i++)
        for (ssf = 0; ssf < SUBSUBFRAMES; ssf++)
            c->masking_curve_cb[ssf][i] = -2047;

    for (ssf = 0; ssf < SUBSUBFRAMES; ssf++)
        for (ch = 0; ch < c->fullband_channels; ch++) {
            const int chi = c->channel_order_tab[ch];

            for (i = 0, k = 128 + 256 * ssf; k < 512; i++, k++)
                data[i] = c->history[ch][k];
            for (k -= 512; i < 512; i++, k++)
                data[i] = input[k * c->channels + chi];
            adjust_jnd(c, data, c->masking_curve_cb[ssf]);
        }
    for (i = 0; i < 256; i++) {
        int32_t m = 2048;

        for (ssf = 0; ssf < SUBSUBFRAMES; ssf++)
            if (c->masking_curve_cb[ssf][i] < m)
                m = c->masking_curve_cb[ssf][i];
        c->eff_masking_curve_cb[i] = m;
    }

    for (band = 0; band < 32; band++) {
        c->band_masking_cb[band] = 2048;
        walk_band_low(c, band, 0, update_band_masking, NULL);
        walk_band_high(c, band, 0, update_band_masking, NULL);
    }
}