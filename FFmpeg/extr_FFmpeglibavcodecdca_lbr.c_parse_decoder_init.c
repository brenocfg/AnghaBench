#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* priv_data; } ;
struct TYPE_10__ {scalar_t__ request_channel_layout; } ;
struct TYPE_9__ {int sample_rate; int band_limit; int nchannels; int ch_mask; int warned; int flags; int bit_rate_orig; int bit_rate_scaled; int nchannels_total; int res_profile; int limited_rate; int limited_range; int nsubbands; int g3_avg_only_start_sb; int min_mono_subband; int max_mono_subband; TYPE_6__* avctx; int /*<<< orphan*/  freq_range; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ DCALbrDecoder ;
typedef  TYPE_2__ DCAContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DCA_LBR_CHANNELS ; 
 int DCA_LBR_CHANNELS_TOTAL ; 
 scalar_t__ DCA_SPEAKER_LAYOUT_STEREO ; 
 int DCA_SPEAKER_PAIR_LFE1 ; 
 int DCA_SPEAKER_PAIR_LR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 unsigned int FF_ARRAY_ELEMS (int*) ; 
#define  LBR_FLAG_BAND_LIMIT_1_2 130 
#define  LBR_FLAG_BAND_LIMIT_1_4 129 
 int LBR_FLAG_BAND_LIMIT_MASK ; 
#define  LBR_FLAG_BAND_LIMIT_NONE 128 
 int LBR_FLAG_DMIX_MULTI_CH ; 
 int LBR_FLAG_DMIX_STEREO ; 
 int LBR_FLAG_LFE_PRESENT ; 
 scalar_t__ alloc_sample_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_6__*,char*,...) ; 
 void* bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int* ff_dca_avg_g3_freqs ; 
 int ff_dca_count_chs_for_mask (int) ; 
 int /*<<< orphan*/ * ff_dca_freq_ranges ; 
 int /*<<< orphan*/  ff_dca_lbr_flush (TYPE_1__*) ; 
 int* ff_dca_sampling_freqs ; 
 scalar_t__ init_sample_rate (TYPE_1__*) ; 

__attribute__((used)) static int parse_decoder_init(DCALbrDecoder *s, GetByteContext *gb)
{
    int old_rate = s->sample_rate;
    int old_band_limit = s->band_limit;
    int old_nchannels = s->nchannels;
    int version, bit_rate_hi;
    unsigned int sr_code;

    // Sample rate of LBR audio
    sr_code = bytestream2_get_byte(gb);
    if (sr_code >= FF_ARRAY_ELEMS(ff_dca_sampling_freqs)) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid LBR sample rate\n");
        return AVERROR_INVALIDDATA;
    }
    s->sample_rate = ff_dca_sampling_freqs[sr_code];
    if (s->sample_rate > 48000) {
        avpriv_report_missing_feature(s->avctx, "%d Hz LBR sample rate", s->sample_rate);
        return AVERROR_PATCHWELCOME;
    }

    // LBR speaker mask
    s->ch_mask = bytestream2_get_le16(gb);
    if (!(s->ch_mask & 0x7)) {
        avpriv_report_missing_feature(s->avctx, "LBR channel mask %#x", s->ch_mask);
        return AVERROR_PATCHWELCOME;
    }
    if ((s->ch_mask & 0xfff0) && !(s->warned & 1)) {
        avpriv_report_missing_feature(s->avctx, "LBR channel mask %#x", s->ch_mask);
        s->warned |= 1;
    }

    // LBR bitstream version
    version = bytestream2_get_le16(gb);
    if ((version & 0xff00) != 0x0800) {
        avpriv_report_missing_feature(s->avctx, "LBR stream version %#x", version);
        return AVERROR_PATCHWELCOME;
    }

    // Flags for LBR decoder initialization
    s->flags = bytestream2_get_byte(gb);
    if (s->flags & LBR_FLAG_DMIX_MULTI_CH) {
        avpriv_report_missing_feature(s->avctx, "LBR multi-channel downmix");
        return AVERROR_PATCHWELCOME;
    }
    if ((s->flags & LBR_FLAG_LFE_PRESENT) && s->sample_rate != 48000) {
        if (!(s->warned & 2)) {
            avpriv_report_missing_feature(s->avctx, "%d Hz LFE interpolation", s->sample_rate);
            s->warned |= 2;
        }
        s->flags &= ~LBR_FLAG_LFE_PRESENT;
    }

    // Most significant bit rate nibbles
    bit_rate_hi = bytestream2_get_byte(gb);

    // Least significant original bit rate word
    s->bit_rate_orig = bytestream2_get_le16(gb) | ((bit_rate_hi & 0x0F) << 16);

    // Least significant scaled bit rate word
    s->bit_rate_scaled = bytestream2_get_le16(gb) | ((bit_rate_hi & 0xF0) << 12);

    // Setup number of fullband channels
    s->nchannels_total = ff_dca_count_chs_for_mask(s->ch_mask & ~DCA_SPEAKER_PAIR_LFE1);
    s->nchannels = FFMIN(s->nchannels_total, DCA_LBR_CHANNELS);

    // Setup band limit
    switch (s->flags & LBR_FLAG_BAND_LIMIT_MASK) {
    case LBR_FLAG_BAND_LIMIT_NONE:
        s->band_limit = 0;
        break;
    case LBR_FLAG_BAND_LIMIT_1_2:
        s->band_limit = 1;
        break;
    case LBR_FLAG_BAND_LIMIT_1_4:
        s->band_limit = 2;
        break;
    default:
        avpriv_report_missing_feature(s->avctx, "LBR band limit %#x", s->flags & LBR_FLAG_BAND_LIMIT_MASK);
        return AVERROR_PATCHWELCOME;
    }

    // Setup frequency range
    s->freq_range = ff_dca_freq_ranges[sr_code];

    // Setup resolution profile
    if (s->bit_rate_orig >= 44000 * (s->nchannels_total + 2))
        s->res_profile = 2;
    else if (s->bit_rate_orig >= 25000 * (s->nchannels_total + 2))
        s->res_profile = 1;
    else
        s->res_profile = 0;

    // Setup limited sample rate, number of subbands, etc
    s->limited_rate = s->sample_rate >> s->band_limit;
    s->limited_range = s->freq_range - s->band_limit;
    if (s->limited_range < 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid LBR band limit for frequency range\n");
        return AVERROR_INVALIDDATA;
    }

    s->nsubbands = 8 << s->limited_range;

    s->g3_avg_only_start_sb = s->nsubbands * ff_dca_avg_g3_freqs[s->res_profile] / (s->limited_rate / 2);
    if (s->g3_avg_only_start_sb > s->nsubbands)
        s->g3_avg_only_start_sb = s->nsubbands;

    s->min_mono_subband = s->nsubbands *  2000 / (s->limited_rate / 2);
    if (s->min_mono_subband > s->nsubbands)
        s->min_mono_subband = s->nsubbands;

    s->max_mono_subband = s->nsubbands * 14000 / (s->limited_rate / 2);
    if (s->max_mono_subband > s->nsubbands)
        s->max_mono_subband = s->nsubbands;

    // Handle change of sample rate
    if ((old_rate != s->sample_rate || old_band_limit != s->band_limit) && init_sample_rate(s) < 0)
        return AVERROR(ENOMEM);

    // Setup stereo downmix
    if (s->flags & LBR_FLAG_DMIX_STEREO) {
        DCAContext *dca = s->avctx->priv_data;

        if (s->nchannels_total < 3 || s->nchannels_total > DCA_LBR_CHANNELS_TOTAL - 2) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid number of channels for LBR stereo downmix\n");
            return AVERROR_INVALIDDATA;
        }

        // This decoder doesn't support ECS chunk
        if (dca->request_channel_layout != DCA_SPEAKER_LAYOUT_STEREO && !(s->warned & 4)) {
            avpriv_report_missing_feature(s->avctx, "Embedded LBR stereo downmix");
            s->warned |= 4;
        }

        // Account for extra downmixed channel pair
        s->nchannels_total += 2;
        s->nchannels = 2;
        s->ch_mask = DCA_SPEAKER_PAIR_LR;
        s->flags &= ~LBR_FLAG_LFE_PRESENT;
    }

    // Handle change of sample rate or number of channels
    if (old_rate != s->sample_rate
        || old_band_limit != s->band_limit
        || old_nchannels != s->nchannels) {
        if (alloc_sample_buffer(s) < 0)
            return AVERROR(ENOMEM);
        ff_dca_lbr_flush(s);
    }

    return 0;
}