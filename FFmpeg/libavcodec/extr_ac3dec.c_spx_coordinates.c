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
typedef  int int64_t ;
struct TYPE_3__ {int fbw_channels; int* first_spx_coords; int spx_src_start_freq; int num_spx_bands; int* spx_band_sizes; float spx_dst_end_freq; int** spx_noise_blend; int** spx_signal_blend; scalar_t__* channel_uses_spx; int /*<<< orphan*/  gbc; } ;
typedef  int INTFLOAT ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 int AC3_SPX_BLEND (int) ; 
 int av_clipf (int,float,float) ; 
 int fixed_sqrt (int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int sqrtf (float) ; 

__attribute__((used)) static inline void spx_coordinates(AC3DecodeContext *s)
{
    GetBitContext *bc = &s->gbc;
    int fbw_channels = s->fbw_channels;
    int ch, bnd;

    for (ch = 1; ch <= fbw_channels; ch++) {
        if (s->channel_uses_spx[ch]) {
            if (s->first_spx_coords[ch] || get_bits1(bc)) {
                INTFLOAT spx_blend;
                int bin, master_spx_coord;

                s->first_spx_coords[ch] = 0;
                spx_blend = AC3_SPX_BLEND(get_bits(bc, 5));
                master_spx_coord = get_bits(bc, 2) * 3;

                bin = s->spx_src_start_freq;
                for (bnd = 0; bnd < s->num_spx_bands; bnd++) {
                    int bandsize = s->spx_band_sizes[bnd];
                    int spx_coord_exp, spx_coord_mant;
                    INTFLOAT nratio, sblend, nblend;
#if USE_FIXED
                    /* calculate blending factors */
                    int64_t accu = ((bin << 23) + (bandsize << 22))
                                 * (int64_t)s->spx_dst_end_freq;
                    nratio = (int)(accu >> 32);
                    nratio -= spx_blend << 18;

                    if (nratio < 0) {
                        nblend = 0;
                        sblend = 0x800000;
                    } else if (nratio > 0x7fffff) {
                        nblend = 14529495; // sqrt(3) in FP.23
                        sblend = 0;
                    } else {
                        nblend = fixed_sqrt(nratio, 23);
                        accu = (int64_t)nblend * 1859775393;
                        nblend = (int)((accu + (1<<29)) >> 30);
                        sblend = fixed_sqrt(0x800000 - nratio, 23);
                    }
#else
                    float spx_coord;

                    /* calculate blending factors */
                    nratio = ((float)((bin + (bandsize >> 1))) / s->spx_dst_end_freq) - spx_blend;
                    nratio = av_clipf(nratio, 0.0f, 1.0f);
                    nblend = sqrtf(3.0f * nratio); // noise is scaled by sqrt(3)
                                                   // to give unity variance
                    sblend = sqrtf(1.0f - nratio);
#endif
                    bin += bandsize;

                    /* decode spx coordinates */
                    spx_coord_exp  = get_bits(bc, 4);
                    spx_coord_mant = get_bits(bc, 2);
                    if (spx_coord_exp == 15) spx_coord_mant <<= 1;
                    else                     spx_coord_mant += 4;
                    spx_coord_mant <<= (25 - spx_coord_exp - master_spx_coord);

                    /* multiply noise and signal blending factors by spx coordinate */
#if USE_FIXED
                    accu = (int64_t)nblend * spx_coord_mant;
                    s->spx_noise_blend[ch][bnd]  = (int)((accu + (1<<22)) >> 23);
                    accu = (int64_t)sblend * spx_coord_mant;
                    s->spx_signal_blend[ch][bnd] = (int)((accu + (1<<22)) >> 23);
#else
                    spx_coord = spx_coord_mant * (1.0f / (1 << 23));
                    s->spx_noise_blend [ch][bnd] = nblend * spx_coord;
                    s->spx_signal_blend[ch][bnd] = sblend * spx_coord;
#endif
                }
            }
        } else {
            s->first_spx_coords[ch] = 1;
        }
    }
}