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
struct TYPE_5__ {int x96_rev_no; int x96_nchannels; int nchannels; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/  x96_crc_present; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_EXSS_CHSETS_MAX ; 
 scalar_t__ DCA_SYNCWORD_X96 ; 
 int alloc_x96_sample_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ff_dca_check_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,int) ; 
 int parse_x96_frame_data (TYPE_1__*,int,int) ; 

__attribute__((used)) static int parse_x96_frame_exss(DCACoreDecoder *s)
{
    int     x96_frame_size[DCA_EXSS_CHSETS_MAX];
    int     x96_nchannels[DCA_EXSS_CHSETS_MAX];
    int     x96_nchsets, x96_base_ch;
    int     i, ret, header_size, header_pos = get_bits_count(&s->gb);

    // X96 sync word
    if (get_bits_long(&s->gb, 32) != DCA_SYNCWORD_X96) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 sync word\n");
        return AVERROR_INVALIDDATA;
    }

    // X96 frame header length
    header_size = get_bits(&s->gb, 6) + 1;

    // Check X96 frame header CRC
    if (ff_dca_check_crc(s->avctx, &s->gb, header_pos + 32, header_pos + header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 frame header checksum\n");
        return AVERROR_INVALIDDATA;
    }

    // Revision number
    s->x96_rev_no = get_bits(&s->gb, 4);
    if (s->x96_rev_no < 1 || s->x96_rev_no > 8) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid X96 revision (%d)\n", s->x96_rev_no);
        return AVERROR_INVALIDDATA;
    }

    // CRC presence flag for channel set header
    s->x96_crc_present = get_bits1(&s->gb);

    // Number of channel sets
    x96_nchsets = get_bits(&s->gb, 2) + 1;

    // Channel set data byte size
    for (i = 0; i < x96_nchsets; i++)
        x96_frame_size[i] = get_bits(&s->gb, 12) + 1;

    // Number of channels in channel set
    for (i = 0; i < x96_nchsets; i++)
        x96_nchannels[i] = get_bits(&s->gb, 3) + 1;

    // Reserved
    // Byte align
    // CRC16 of X96 frame header
    if (ff_dca_seek_bits(&s->gb, header_pos + header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of X96 frame header\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = alloc_x96_sample_buffer(s)) < 0)
        return ret;

    // Channel set data
    s->x96_nchannels = 0;
    for (i = 0, x96_base_ch = 0; i < x96_nchsets; i++) {
        header_pos = get_bits_count(&s->gb);

        if (x96_base_ch + x96_nchannels[i] <= s->nchannels) {
            s->x96_nchannels = x96_base_ch + x96_nchannels[i];
            if ((ret = parse_x96_frame_data(s, 1, x96_base_ch)) < 0)
                return ret;
        }

        x96_base_ch += x96_nchannels[i];

        if (ff_dca_seek_bits(&s->gb, header_pos + x96_frame_size[i] * 8)) {
            av_log(s->avctx, AV_LOG_ERROR, "Read past end of X96 channel set\n");
            return AVERROR_INVALIDDATA;
        }
    }

    return 0;
}