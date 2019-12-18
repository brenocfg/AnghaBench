#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum HeaderType { ____Placeholder_HeaderType } HeaderType ;
struct TYPE_5__ {int* nsubsubframes; int nchannels; int* nsubbands; int* bit_allocation_sel; int* subband_vq_start; int** bit_allocation; int* transition_mode_sel; int* scale_factor_sel; int*** scale_factors; int* joint_intensity_index; int* joint_scale_sel; int** joint_scale_factors; int /*<<< orphan*/  gb; scalar_t__ crc_present; scalar_t__ drc_present; int /*<<< orphan*/  avctx; void**** transition_mode; void*** prediction_vq_index; scalar_t__** prediction_mode; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_ABITS_MAX ; 
 int HEADER_CORE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* dca_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_dca_vlc_bit_allocation ; 
 int /*<<< orphan*/  ff_dca_vlc_transition_mode ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 int parse_joint_scale (TYPE_1__*,int) ; 
 int parse_scale (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_subframe_header(DCACoreDecoder *s, int sf,
                                 enum HeaderType header, int xch_base)
{
    int ch, band, ret;

    if (get_bits_left(&s->gb) < 0)
        return AVERROR_INVALIDDATA;

    if (header == HEADER_CORE) {
        // Subsubframe count
        s->nsubsubframes[sf] = get_bits(&s->gb, 2) + 1;

        // Partial subsubframe sample count
        skip_bits(&s->gb, 3);
    }

    // Prediction mode
    for (ch = xch_base; ch < s->nchannels; ch++)
        for (band = 0; band < s->nsubbands[ch]; band++)
            s->prediction_mode[ch][band] = get_bits1(&s->gb);

    // Prediction coefficients VQ address
    for (ch = xch_base; ch < s->nchannels; ch++)
        for (band = 0; band < s->nsubbands[ch]; band++)
            if (s->prediction_mode[ch][band])
                s->prediction_vq_index[ch][band] = get_bits(&s->gb, 12);

    // Bit allocation index
    for (ch = xch_base; ch < s->nchannels; ch++) {
        int sel = s->bit_allocation_sel[ch];

        for (band = 0; band < s->subband_vq_start[ch]; band++) {
            int abits;

            if (sel < 5)
                abits = dca_get_vlc(&s->gb, &ff_dca_vlc_bit_allocation, sel);
            else
                abits = get_bits(&s->gb, sel - 1);

            if (abits > DCA_ABITS_MAX) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid bit allocation index\n");
                return AVERROR_INVALIDDATA;
            }

            s->bit_allocation[ch][band] = abits;
        }
    }

    // Transition mode
    for (ch = xch_base; ch < s->nchannels; ch++) {
        // Clear transition mode for all subbands
        memset(s->transition_mode[sf][ch], 0, sizeof(s->transition_mode[0][0]));

        // Transient possible only if more than one subsubframe
        if (s->nsubsubframes[sf] > 1) {
            int sel = s->transition_mode_sel[ch];
            for (band = 0; band < s->subband_vq_start[ch]; band++)
                if (s->bit_allocation[ch][band])
                    s->transition_mode[sf][ch][band] = dca_get_vlc(&s->gb, &ff_dca_vlc_transition_mode, sel);
        }
    }

    // Scale factors
    for (ch = xch_base; ch < s->nchannels; ch++) {
        int sel = s->scale_factor_sel[ch];
        int scale_index = 0;

        // Extract scales for subbands up to VQ
        for (band = 0; band < s->subband_vq_start[ch]; band++) {
            if (s->bit_allocation[ch][band]) {
                if ((ret = parse_scale(s, &scale_index, sel)) < 0)
                    return ret;
                s->scale_factors[ch][band][0] = ret;
                if (s->transition_mode[sf][ch][band]) {
                    if ((ret = parse_scale(s, &scale_index, sel)) < 0)
                        return ret;
                    s->scale_factors[ch][band][1] = ret;
                }
            } else {
                s->scale_factors[ch][band][0] = 0;
            }
        }

        // High frequency VQ subbands
        for (band = s->subband_vq_start[ch]; band < s->nsubbands[ch]; band++) {
            if ((ret = parse_scale(s, &scale_index, sel)) < 0)
                return ret;
            s->scale_factors[ch][band][0] = ret;
        }
    }

    // Joint subband codebook select
    for (ch = xch_base; ch < s->nchannels; ch++) {
        if (s->joint_intensity_index[ch]) {
            s->joint_scale_sel[ch] = get_bits(&s->gb, 3);
            if (s->joint_scale_sel[ch] == 7) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid joint scale factor code book\n");
                return AVERROR_INVALIDDATA;
            }
        }
    }

    // Scale factors for joint subband coding
    for (ch = xch_base; ch < s->nchannels; ch++) {
        int src_ch = s->joint_intensity_index[ch] - 1;
        if (src_ch >= 0) {
            int sel = s->joint_scale_sel[ch];
            for (band = s->nsubbands[ch]; band < s->nsubbands[src_ch]; band++) {
                if ((ret = parse_joint_scale(s, sel)) < 0)
                    return ret;
                s->joint_scale_factors[ch][band] = ret;
            }
        }
    }

    // Dynamic range coefficient
    if (s->drc_present && header == HEADER_CORE)
        skip_bits(&s->gb, 8);

    // Side information CRC check word
    if (s->crc_present)
        skip_bits(&s->gb, 16);

    return 0;
}