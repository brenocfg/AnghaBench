#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fullband_channels; int** prediction_mode; int* bit_allocation_sel; int** abits; int** scale_factor; int lfe_scale_factor; int /*<<< orphan*/  pb; int /*<<< orphan*/  lfe_quant; int /*<<< orphan*/ * downsampled_lfe; scalar_t__ lfe_channel; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int DCAENC_SUBBANDS ; 
 int DCA_LFE_SAMPLES ; 
 int SUBSUBFRAMES ; 
 int /*<<< orphan*/  ff_dca_vlc_enc_alloc (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_subframe_samples (TYPE_1__*,int,int,int) ; 
 int quantize_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_subframe(DCAEncContext *c, int subframe)
{
    int i, band, ss, ch;

    /* Subsubframes count */
    put_bits(&c->pb, 2, SUBSUBFRAMES -1);

    /* Partial subsubframe sample count: dummy */
    put_bits(&c->pb, 3, 0);

    /* Prediction mode: no ADPCM, in each channel and subband */
    for (ch = 0; ch < c->fullband_channels; ch++)
        for (band = 0; band < DCAENC_SUBBANDS; band++)
            put_bits(&c->pb, 1, !(c->prediction_mode[ch][band] == -1));

    /* Prediction VQ address */
    for (ch = 0; ch < c->fullband_channels; ch++)
        for (band = 0; band < DCAENC_SUBBANDS; band++)
            if (c->prediction_mode[ch][band] >= 0)
                put_bits(&c->pb, 12, c->prediction_mode[ch][band]);

    /* Bit allocation index */
    for (ch = 0; ch < c->fullband_channels; ch++) {
        if (c->bit_allocation_sel[ch] == 6) {
            for (band = 0; band < DCAENC_SUBBANDS; band++) {
                put_bits(&c->pb, 5, c->abits[ch][band]);
            }
        } else {
            ff_dca_vlc_enc_alloc(&c->pb, c->abits[ch], DCAENC_SUBBANDS,
                                 c->bit_allocation_sel[ch]);
        }
    }

    if (SUBSUBFRAMES > 1) {
        /* Transition mode: none for each channel and subband */
        for (ch = 0; ch < c->fullband_channels; ch++)
            for (band = 0; band < DCAENC_SUBBANDS; band++)
                if (c->abits[ch][band])
                    put_bits(&c->pb, 1, 0); /* codebook A4 */
    }

    /* Scale factors */
    for (ch = 0; ch < c->fullband_channels; ch++)
        for (band = 0; band < DCAENC_SUBBANDS; band++)
            if (c->abits[ch][band])
                put_bits(&c->pb, 7, c->scale_factor[ch][band]);

    /* Joint subband scale factor codebook select: not transmitted */
    /* Scale factors for joint subband coding: not transmitted */
    /* Stereo down-mix coefficients: not transmitted */
    /* Dynamic range coefficient: not transmitted */
    /* Stde information CRC check word: not transmitted */
    /* VQ encoded high frequency subbands: not transmitted */

    /* LFE data: 8 samples and scalefactor */
    if (c->lfe_channel) {
        for (i = 0; i < DCA_LFE_SAMPLES; i++)
            put_bits(&c->pb, 8, quantize_value(c->downsampled_lfe[i], c->lfe_quant) & 0xff);
        put_bits(&c->pb, 8, c->lfe_scale_factor);
    }

    /* Audio data (subsubframes) */
    for (ss = 0; ss < SUBSUBFRAMES ; ss++)
        for (ch = 0; ch < c->fullband_channels; ch++)
            for (band = 0; band < DCAENC_SUBBANDS; band++)
                if (c->abits[ch][band])
                    put_subframe_samples(c, ss, band, ch);

    /* DSYNC */
    put_bits(&c->pb, 16, 0xffff);
}