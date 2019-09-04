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
struct TYPE_3__ {int x96_high_res; int x96_rev_no; int x96_subband_start; int x96_nchannels; int* nsubbands; int* joint_intensity_index; int* scale_factor_sel; int /*<<< orphan*/  gb; scalar_t__ crc_present; int /*<<< orphan*/  avctx; void*** quant_index_sel; void** bit_allocation_sel; scalar_t__ x96_crc_present; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_SUBBANDS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ff_dca_check_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int* ff_dca_quant_index_sel_nbits ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_x96_coding_header(DCACoreDecoder *s, int exss, int xch_base)
{
    int n, ch, header_size = 0, header_pos = get_bits_count(&s->gb);

    if (get_bits_left(&s->gb) < 0)
        return AVERROR_INVALIDDATA;

    if (exss) {
        // Channel set header length
        header_size = get_bits(&s->gb, 7) + 1;

        // Check CRC
        if (s->x96_crc_present
            && ff_dca_check_crc(s->avctx, &s->gb, header_pos, header_pos + header_size * 8)) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 channel set header checksum\n");
            return AVERROR_INVALIDDATA;
        }
    }

    // High resolution flag
    s->x96_high_res = get_bits1(&s->gb);

    // First encoded subband
    if (s->x96_rev_no < 8) {
        s->x96_subband_start = get_bits(&s->gb, 5);
        if (s->x96_subband_start > 27) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 subband start index (%d)\n", s->x96_subband_start);
            return AVERROR_INVALIDDATA;
        }
    } else {
        s->x96_subband_start = DCA_SUBBANDS;
    }

    // Subband activity count
    for (ch = xch_base; ch < s->x96_nchannels; ch++) {
        s->nsubbands[ch] = get_bits(&s->gb, 6) + 1;
        if (s->nsubbands[ch] < DCA_SUBBANDS) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 subband activity count (%d)\n", s->nsubbands[ch]);
            return AVERROR_INVALIDDATA;
        }
    }

    // Joint intensity coding index
    for (ch = xch_base; ch < s->x96_nchannels; ch++) {
        if ((n = get_bits(&s->gb, 3)) && xch_base)
            n += xch_base - 1;
        if (n > s->x96_nchannels) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 joint intensity coding index\n");
            return AVERROR_INVALIDDATA;
        }
        s->joint_intensity_index[ch] = n;
    }

    // Scale factor code book
    for (ch = xch_base; ch < s->x96_nchannels; ch++) {
        s->scale_factor_sel[ch] = get_bits(&s->gb, 3);
        if (s->scale_factor_sel[ch] >= 6) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 scale factor code book\n");
            return AVERROR_INVALIDDATA;
        }
    }

    // Bit allocation quantizer select
    for (ch = xch_base; ch < s->x96_nchannels; ch++)
        s->bit_allocation_sel[ch] = get_bits(&s->gb, 3);

    // Quantization index codebook select
    for (n = 0; n < 6 + 4 * s->x96_high_res; n++)
        for (ch = xch_base; ch < s->x96_nchannels; ch++)
            s->quant_index_sel[ch][n] = get_bits(&s->gb, ff_dca_quant_index_sel_nbits[n]);

    if (exss) {
        // Reserved
        // Byte align
        // CRC16 of channel set header
        if (ff_dca_seek_bits(&s->gb, header_pos + header_size * 8)) {
            av_log(s->avctx, AV_LOG_ERROR, "Read past end of X96 channel set header\n");
            return AVERROR_INVALIDDATA;
        }
    } else {
        if (s->crc_present)
            skip_bits(&s->gb, 16);
    }

    return 0;
}