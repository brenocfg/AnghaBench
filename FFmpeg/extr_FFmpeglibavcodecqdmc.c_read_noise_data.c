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
struct TYPE_3__ {int nb_channels; size_t band_index; int*** noise; } ;
typedef  TYPE_1__ QDMCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int* noise_bands_size ; 
 int qdmc_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vtable ; 

__attribute__((used)) static int read_noise_data(QDMCContext *s, GetBitContext *gb)
{
    int ch, j, k, v, idx, band, lastval, newval, len;

    for (ch = 0; ch < s->nb_channels; ch++) {
        for (band = 0; band < noise_bands_size[s->band_index]; band++) {
            v = qdmc_get_vlc(gb, &vtable[0], 0);
            if (v < 0)
                return AVERROR_INVALIDDATA;

            if (v & 1)
                v = v + 1;
            else
                v = -v;

            lastval = v / 2;
            s->noise[ch][band][0] = lastval - 1;
            for (j = 0; j < 15;) {
                len = qdmc_get_vlc(gb, &vtable[1], 1);
                if (len < 0)
                    return AVERROR_INVALIDDATA;
                len += 1;

                v = qdmc_get_vlc(gb, &vtable[0], 0);
                if (v < 0)
                    return AVERROR_INVALIDDATA;

                if (v & 1)
                    newval = lastval + (v + 1) / 2;
                else
                    newval = lastval - v / 2;

                idx = j + 1;
                if (len + idx > 16)
                    return AVERROR_INVALIDDATA;

                for (k = 1; idx <= j + len; k++, idx++)
                    s->noise[ch][band][idx] = lastval + k * (newval - lastval) / len - 1;

                lastval = newval;
                j += len;
            }
        }
    }

    return 0;
}