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
struct TYPE_4__ {int xxch_mask_nbits; int xxch_core_mask; int ch_mask; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/  nchannels; int /*<<< orphan*/  xxch_crc_present; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int DCA_SPEAKER_Cs ; 
 int DCA_SPEAKER_MASK_Ls ; 
 int DCA_SPEAKER_MASK_Lss ; 
 int DCA_SPEAKER_MASK_Rs ; 
 int DCA_SPEAKER_MASK_Rss ; 
 scalar_t__ DCA_SYNCWORD_XXCH ; 
 int /*<<< orphan*/  HEADER_XXCH ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ff_dca_check_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ff_dca_seek_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,int) ; 
 int parse_frame_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_xxch_frame(DCACoreDecoder *s)
{
    int xxch_nchsets, xxch_frame_size;
    int ret, mask, header_size, header_pos = get_bits_count(&s->gb);

    // XXCH sync word
    if (get_bits_long(&s->gb, 32) != DCA_SYNCWORD_XXCH) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid XXCH sync word\n");
        return AVERROR_INVALIDDATA;
    }

    // XXCH frame header length
    header_size = get_bits(&s->gb, 6) + 1;

    // Check XXCH frame header CRC
    if (ff_dca_check_crc(s->avctx, &s->gb, header_pos + 32, header_pos + header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid XXCH frame header checksum\n");
        return AVERROR_INVALIDDATA;
    }

    // CRC presence flag for channel set header
    s->xxch_crc_present = get_bits1(&s->gb);

    // Number of bits for loudspeaker mask
    s->xxch_mask_nbits = get_bits(&s->gb, 5) + 1;
    if (s->xxch_mask_nbits <= DCA_SPEAKER_Cs) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid number of bits for XXCH speaker mask (%d)\n", s->xxch_mask_nbits);
        return AVERROR_INVALIDDATA;
    }

    // Number of channel sets
    xxch_nchsets = get_bits(&s->gb, 2) + 1;
    if (xxch_nchsets > 1) {
        avpriv_request_sample(s->avctx, "%d XXCH channel sets", xxch_nchsets);
        return AVERROR_PATCHWELCOME;
    }

    // Channel set 0 data byte size
    xxch_frame_size = get_bits(&s->gb, 14) + 1;

    // Core loudspeaker activity mask
    s->xxch_core_mask = get_bits_long(&s->gb, s->xxch_mask_nbits);

    // Validate the core mask
    mask = s->ch_mask;

    if ((mask & DCA_SPEAKER_MASK_Ls) && (s->xxch_core_mask & DCA_SPEAKER_MASK_Lss))
        mask = (mask & ~DCA_SPEAKER_MASK_Ls) | DCA_SPEAKER_MASK_Lss;

    if ((mask & DCA_SPEAKER_MASK_Rs) && (s->xxch_core_mask & DCA_SPEAKER_MASK_Rss))
        mask = (mask & ~DCA_SPEAKER_MASK_Rs) | DCA_SPEAKER_MASK_Rss;

    if (mask != s->xxch_core_mask) {
        av_log(s->avctx, AV_LOG_ERROR, "XXCH core speaker activity mask (%#x) disagrees with core (%#x)\n", s->xxch_core_mask, mask);
        return AVERROR_INVALIDDATA;
    }

    // Reserved
    // Byte align
    // CRC16 of XXCH frame header
    if (ff_dca_seek_bits(&s->gb, header_pos + header_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of XXCH frame header\n");
        return AVERROR_INVALIDDATA;
    }

    // Parse XXCH channel set 0
    if ((ret = parse_frame_data(s, HEADER_XXCH, s->nchannels)) < 0)
        return ret;

    if (ff_dca_seek_bits(&s->gb, header_pos + header_size * 8 + xxch_frame_size * 8)) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of XXCH channel set\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}