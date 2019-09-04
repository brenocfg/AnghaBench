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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int* nsubsubframes; int npcmblocks; int* scale_factor_sel; int*** transition_mode; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; scalar_t__ sync_ssf; scalar_t__** subband_samples; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_ABITS_MAX ; 
 int DCA_CHANNELS ; 
 int DCA_SUBBANDS ; 
 int DCA_SUBBAND_SAMPLES ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_dca_core_dequantize (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ff_dca_lossless_quant ; 
 int /*<<< orphan*/ * ff_dca_scale_factor_quant6 ; 
 int /*<<< orphan*/ * ff_dca_scale_factor_quant7 ; 
 int /*<<< orphan*/  get_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int parse_block_codes (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_xbr_subframe(DCACoreDecoder *s, int xbr_base_ch, int xbr_nchannels,
                              int *xbr_nsubbands, int xbr_transition_mode, int sf, int *sub_pos)
{
    int     xbr_nabits[DCA_CHANNELS];
    int     xbr_bit_allocation[DCA_CHANNELS][DCA_SUBBANDS];
    int     xbr_scale_nbits[DCA_CHANNELS];
    int32_t xbr_scale_factors[DCA_CHANNELS][DCA_SUBBANDS][2];
    int     ssf, ch, band, ofs;

    // Check number of subband samples in this subframe
    if (*sub_pos + s->nsubsubframes[sf] * DCA_SUBBAND_SAMPLES > s->npcmblocks) {
        av_log(s->avctx, AV_LOG_ERROR, "Subband sample buffer overflow\n");
        return AVERROR_INVALIDDATA;
    }

    if (get_bits_left(&s->gb) < 0)
        return AVERROR_INVALIDDATA;

    // Number of bits for XBR bit allocation index
    for (ch = xbr_base_ch; ch < xbr_nchannels; ch++)
        xbr_nabits[ch] = get_bits(&s->gb, 2) + 2;

    // XBR bit allocation index
    for (ch = xbr_base_ch; ch < xbr_nchannels; ch++) {
        for (band = 0; band < xbr_nsubbands[ch]; band++) {
            xbr_bit_allocation[ch][band] = get_bits(&s->gb, xbr_nabits[ch]);
            if (xbr_bit_allocation[ch][band] > DCA_ABITS_MAX) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid XBR bit allocation index\n");
                return AVERROR_INVALIDDATA;
            }
        }
    }

    // Number of bits for scale indices
    for (ch = xbr_base_ch; ch < xbr_nchannels; ch++) {
        xbr_scale_nbits[ch] = get_bits(&s->gb, 3);
        if (!xbr_scale_nbits[ch]) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid number of bits for XBR scale factor index\n");
            return AVERROR_INVALIDDATA;
        }
    }

    // XBR scale factors
    for (ch = xbr_base_ch; ch < xbr_nchannels; ch++) {
        const uint32_t *scale_table;
        int scale_size;

        // Select the root square table
        if (s->scale_factor_sel[ch] > 5) {
            scale_table = ff_dca_scale_factor_quant7;
            scale_size = FF_ARRAY_ELEMS(ff_dca_scale_factor_quant7);
        } else {
            scale_table = ff_dca_scale_factor_quant6;
            scale_size = FF_ARRAY_ELEMS(ff_dca_scale_factor_quant6);
        }

        // Parse scale factor indices and look up scale factors from the root
        // square table
        for (band = 0; band < xbr_nsubbands[ch]; band++) {
            if (xbr_bit_allocation[ch][band]) {
                int scale_index = get_bits(&s->gb, xbr_scale_nbits[ch]);
                if (scale_index >= scale_size) {
                    av_log(s->avctx, AV_LOG_ERROR, "Invalid XBR scale factor index\n");
                    return AVERROR_INVALIDDATA;
                }
                xbr_scale_factors[ch][band][0] = scale_table[scale_index];
                if (xbr_transition_mode && s->transition_mode[sf][ch][band]) {
                    scale_index = get_bits(&s->gb, xbr_scale_nbits[ch]);
                    if (scale_index >= scale_size) {
                        av_log(s->avctx, AV_LOG_ERROR, "Invalid XBR scale factor index\n");
                        return AVERROR_INVALIDDATA;
                    }
                    xbr_scale_factors[ch][band][1] = scale_table[scale_index];
                }
            }
        }
    }

    // Audio data
    for (ssf = 0, ofs = *sub_pos; ssf < s->nsubsubframes[sf]; ssf++) {
        for (ch = xbr_base_ch; ch < xbr_nchannels; ch++) {
            if (get_bits_left(&s->gb) < 0)
                return AVERROR_INVALIDDATA;

            for (band = 0; band < xbr_nsubbands[ch]; band++) {
                int ret, trans_ssf, abits = xbr_bit_allocation[ch][band];
                int32_t audio[DCA_SUBBAND_SAMPLES], step_size, scale;

                // Extract bits from the bit stream
                if (abits > 7) {
                    // No further encoding
                    get_array(&s->gb, audio, DCA_SUBBAND_SAMPLES, abits - 3);
                } else if (abits > 0) {
                    // Block codes
                    if ((ret = parse_block_codes(s, audio, abits)) < 0)
                        return ret;
                } else {
                    // No bits allocated
                    continue;
                }

                // Look up quantization step size
                step_size = ff_dca_lossless_quant[abits];

                // Identify transient location
                if (xbr_transition_mode)
                    trans_ssf = s->transition_mode[sf][ch][band];
                else
                    trans_ssf = 0;

                // Determine proper scale factor
                if (trans_ssf == 0 || ssf < trans_ssf)
                    scale = xbr_scale_factors[ch][band][0];
                else
                    scale = xbr_scale_factors[ch][band][1];

                ff_dca_core_dequantize(s->subband_samples[ch][band] + ofs,
                           audio, step_size, scale, 1, DCA_SUBBAND_SAMPLES);
            }
        }

        // DSYNC
        if ((ssf == s->nsubsubframes[sf] - 1 || s->sync_ssf) && get_bits(&s->gb, 16) != 0xffff) {
            av_log(s->avctx, AV_LOG_ERROR, "XBR-DSYNC check failed\n");
            return AVERROR_INVALIDDATA;
        }

        ofs += DCA_SUBBAND_SAMPLES;
    }

    // Advance subband sample pointer for the next subframe
    *sub_pos = ofs;
    return 0;
}