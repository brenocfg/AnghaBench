#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int samples_per_frame; int nb_channels; scalar_t__ subframe_offset; size_t channels_for_cur_subframe; int* channel_indexes_for_cur_subframe; int parsed_all_subframes; size_t table_idx; int num_bands; int* num_sfb; int* cur_sfb_offsets; int** sfb_offsets; int* subwoofer_cutoffs; int subframe_len; int esc_len; scalar_t__ num_saved_bits; int bits_per_sample; int lfe_channel; TYPE_2__* channel; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * tmp; TYPE_1__* fdsp; TYPE_4__* mdct_ctx; int /*<<< orphan*/  gb; void* transmit_num_vec_coeffs; } ;
typedef  TYPE_3__ WMAProDecodeCtx ;
struct TYPE_15__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {int decoded_samples; int* subframe_len; size_t cur_subframe; int num_vec_coeffs; int quant_step; int* scale_factors; int max_scale_factor; int scale_factor_step; scalar_t__ num_subframes; int /*<<< orphan*/ * coeffs; void* transmit_coefs; int /*<<< orphan*/ * out; scalar_t__ grouped; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* vector_fmul_scalar ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float const,int const) ;} ;
typedef  TYPE_4__ FFTContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int WMAPRO_BLOCK_MAX_SIZE ; 
 size_t WMAPRO_BLOCK_MIN_BITS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 size_t av_log2 (int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ decode_channel_transform (TYPE_3__*) ; 
 int /*<<< orphan*/  decode_coeffs (TYPE_3__*,int) ; 
 scalar_t__ decode_scale_factors (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 float ff_exp10 (int const) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bitsz (int /*<<< orphan*/ *,int) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inverse_channel_transform (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float const,int const) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmapro_window (TYPE_3__*) ; 

__attribute__((used)) static int decode_subframe(WMAProDecodeCtx *s)
{
    int offset = s->samples_per_frame;
    int subframe_len = s->samples_per_frame;
    int i;
    int total_samples   = s->samples_per_frame * s->nb_channels;
    int transmit_coeffs = 0;
    int cur_subwoofer_cutoff;

    s->subframe_offset = get_bits_count(&s->gb);

    /** reset channel context and find the next block offset and size
        == the next block of the channel with the smallest number of
        decoded samples
    */
    for (i = 0; i < s->nb_channels; i++) {
        s->channel[i].grouped = 0;
        if (offset > s->channel[i].decoded_samples) {
            offset = s->channel[i].decoded_samples;
            subframe_len =
                s->channel[i].subframe_len[s->channel[i].cur_subframe];
        }
    }

    ff_dlog(s->avctx,
            "processing subframe with offset %i len %i\n", offset, subframe_len);

    /** get a list of all channels that contain the estimated block */
    s->channels_for_cur_subframe = 0;
    for (i = 0; i < s->nb_channels; i++) {
        const int cur_subframe = s->channel[i].cur_subframe;
        /** subtract already processed samples */
        total_samples -= s->channel[i].decoded_samples;

        /** and count if there are multiple subframes that match our profile */
        if (offset == s->channel[i].decoded_samples &&
            subframe_len == s->channel[i].subframe_len[cur_subframe]) {
            total_samples -= s->channel[i].subframe_len[cur_subframe];
            s->channel[i].decoded_samples +=
                s->channel[i].subframe_len[cur_subframe];
            s->channel_indexes_for_cur_subframe[s->channels_for_cur_subframe] = i;
            ++s->channels_for_cur_subframe;
        }
    }

    /** check if the frame will be complete after processing the
        estimated block */
    if (!total_samples)
        s->parsed_all_subframes = 1;


    ff_dlog(s->avctx, "subframe is part of %i channels\n",
            s->channels_for_cur_subframe);

    /** calculate number of scale factor bands and their offsets */
    s->table_idx         = av_log2(s->samples_per_frame/subframe_len);
    s->num_bands         = s->num_sfb[s->table_idx];
    s->cur_sfb_offsets   = s->sfb_offsets[s->table_idx];
    cur_subwoofer_cutoff = s->subwoofer_cutoffs[s->table_idx];

    /** configure the decoder for the current subframe */
    offset += s->samples_per_frame >> 1;

    for (i = 0; i < s->channels_for_cur_subframe; i++) {
        int c = s->channel_indexes_for_cur_subframe[i];

        s->channel[c].coeffs = &s->channel[c].out[offset];
    }

    s->subframe_len = subframe_len;
    s->esc_len = av_log2(s->subframe_len - 1) + 1;

    /** skip extended header if any */
    if (get_bits1(&s->gb)) {
        int num_fill_bits;
        if (!(num_fill_bits = get_bits(&s->gb, 2))) {
            int len = get_bits(&s->gb, 4);
            num_fill_bits = get_bitsz(&s->gb, len) + 1;
        }

        if (num_fill_bits >= 0) {
            if (get_bits_count(&s->gb) + num_fill_bits > s->num_saved_bits) {
                av_log(s->avctx, AV_LOG_ERROR, "invalid number of fill bits\n");
                return AVERROR_INVALIDDATA;
            }

            skip_bits_long(&s->gb, num_fill_bits);
        }
    }

    /** no idea for what the following bit is used */
    if (get_bits1(&s->gb)) {
        avpriv_request_sample(s->avctx, "Reserved bit");
        return AVERROR_PATCHWELCOME;
    }


    if (decode_channel_transform(s) < 0)
        return AVERROR_INVALIDDATA;


    for (i = 0; i < s->channels_for_cur_subframe; i++) {
        int c = s->channel_indexes_for_cur_subframe[i];
        if ((s->channel[c].transmit_coefs = get_bits1(&s->gb)))
            transmit_coeffs = 1;
    }

    av_assert0(s->subframe_len <= WMAPRO_BLOCK_MAX_SIZE);
    if (transmit_coeffs) {
        int step;
        int quant_step = 90 * s->bits_per_sample >> 4;

        /** decode number of vector coded coefficients */
        if ((s->transmit_num_vec_coeffs = get_bits1(&s->gb))) {
            int num_bits = av_log2((s->subframe_len + 3)/4) + 1;
            for (i = 0; i < s->channels_for_cur_subframe; i++) {
                int c = s->channel_indexes_for_cur_subframe[i];
                int num_vec_coeffs = get_bits(&s->gb, num_bits) << 2;
                if (num_vec_coeffs > s->subframe_len) {
                    av_log(s->avctx, AV_LOG_ERROR, "num_vec_coeffs %d is too large\n", num_vec_coeffs);
                    return AVERROR_INVALIDDATA;
                }
                av_assert0(num_vec_coeffs + offset <= FF_ARRAY_ELEMS(s->channel[c].out));
                s->channel[c].num_vec_coeffs = num_vec_coeffs;
            }
        } else {
            for (i = 0; i < s->channels_for_cur_subframe; i++) {
                int c = s->channel_indexes_for_cur_subframe[i];
                s->channel[c].num_vec_coeffs = s->subframe_len;
            }
        }
        /** decode quantization step */
        step = get_sbits(&s->gb, 6);
        quant_step += step;
        if (step == -32 || step == 31) {
            const int sign = (step == 31) - 1;
            int quant = 0;
            while (get_bits_count(&s->gb) + 5 < s->num_saved_bits &&
                   (step = get_bits(&s->gb, 5)) == 31) {
                quant += 31;
            }
            quant_step += ((quant + step) ^ sign) - sign;
        }
        if (quant_step < 0) {
            av_log(s->avctx, AV_LOG_DEBUG, "negative quant step\n");
        }

        /** decode quantization step modifiers for every channel */

        if (s->channels_for_cur_subframe == 1) {
            s->channel[s->channel_indexes_for_cur_subframe[0]].quant_step = quant_step;
        } else {
            int modifier_len = get_bits(&s->gb, 3);
            for (i = 0; i < s->channels_for_cur_subframe; i++) {
                int c = s->channel_indexes_for_cur_subframe[i];
                s->channel[c].quant_step = quant_step;
                if (get_bits1(&s->gb)) {
                    if (modifier_len) {
                        s->channel[c].quant_step += get_bits(&s->gb, modifier_len) + 1;
                    } else
                        ++s->channel[c].quant_step;
                }
            }
        }

        /** decode scale factors */
        if (decode_scale_factors(s) < 0)
            return AVERROR_INVALIDDATA;
    }

    ff_dlog(s->avctx, "BITSTREAM: subframe header length was %i\n",
            get_bits_count(&s->gb) - s->subframe_offset);

    /** parse coefficients */
    for (i = 0; i < s->channels_for_cur_subframe; i++) {
        int c = s->channel_indexes_for_cur_subframe[i];
        if (s->channel[c].transmit_coefs &&
            get_bits_count(&s->gb) < s->num_saved_bits) {
            decode_coeffs(s, c);
        } else
            memset(s->channel[c].coeffs, 0,
                   sizeof(*s->channel[c].coeffs) * subframe_len);
    }

    ff_dlog(s->avctx, "BITSTREAM: subframe length was %i\n",
            get_bits_count(&s->gb) - s->subframe_offset);

    if (transmit_coeffs) {
        FFTContext *mdct = &s->mdct_ctx[av_log2(subframe_len) - WMAPRO_BLOCK_MIN_BITS];
        /** reconstruct the per channel data */
        inverse_channel_transform(s);
        for (i = 0; i < s->channels_for_cur_subframe; i++) {
            int c = s->channel_indexes_for_cur_subframe[i];
            const int* sf = s->channel[c].scale_factors;
            int b;

            if (c == s->lfe_channel)
                memset(&s->tmp[cur_subwoofer_cutoff], 0, sizeof(*s->tmp) *
                       (subframe_len - cur_subwoofer_cutoff));

            /** inverse quantization and rescaling */
            for (b = 0; b < s->num_bands; b++) {
                const int end = FFMIN(s->cur_sfb_offsets[b+1], s->subframe_len);
                const int exp = s->channel[c].quant_step -
                            (s->channel[c].max_scale_factor - *sf++) *
                            s->channel[c].scale_factor_step;
                const float quant = ff_exp10(exp / 20.0);
                int start = s->cur_sfb_offsets[b];
                s->fdsp->vector_fmul_scalar(s->tmp + start,
                                           s->channel[c].coeffs + start,
                                           quant, end - start);
            }

            /** apply imdct (imdct_half == DCTIV with reverse) */
            mdct->imdct_half(mdct, s->channel[c].coeffs, s->tmp);
        }
    }

    /** window and overlapp-add */
    wmapro_window(s);

    /** handled one subframe */
    for (i = 0; i < s->channels_for_cur_subframe; i++) {
        int c = s->channel_indexes_for_cur_subframe[i];
        if (s->channel[c].cur_subframe >= s->channel[c].num_subframes) {
            av_log(s->avctx, AV_LOG_ERROR, "broken subframe\n");
            return AVERROR_INVALIDDATA;
        }
        ++s->channel[c].cur_subframe;
    }

    return 0;
}