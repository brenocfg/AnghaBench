#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AC3EncodeContext ;

/* Variables and functions */

__attribute__((used)) static void dprint_options(AC3EncodeContext *s)
{
#ifdef DEBUG
    AVCodecContext *avctx = s->avctx;
    AC3EncOptions *opt = &s->options;
    char strbuf[32];

    switch (s->bitstream_id) {
    case  6:  av_strlcpy(strbuf, "AC-3 (alt syntax)",       32); break;
    case  8:  av_strlcpy(strbuf, "AC-3 (standard)",         32); break;
    case  9:  av_strlcpy(strbuf, "AC-3 (dnet half-rate)",   32); break;
    case 10:  av_strlcpy(strbuf, "AC-3 (dnet quater-rate)", 32); break;
    case 16:  av_strlcpy(strbuf, "E-AC-3 (enhanced)",       32); break;
    default: snprintf(strbuf, 32, "ERROR");
    }
    ff_dlog(avctx, "bitstream_id: %s (%d)\n", strbuf, s->bitstream_id);
    ff_dlog(avctx, "sample_fmt: %s\n", av_get_sample_fmt_name(avctx->sample_fmt));
    av_get_channel_layout_string(strbuf, 32, s->channels, avctx->channel_layout);
    ff_dlog(avctx, "channel_layout: %s\n", strbuf);
    ff_dlog(avctx, "sample_rate: %d\n", s->sample_rate);
    ff_dlog(avctx, "bit_rate: %d\n", s->bit_rate);
    ff_dlog(avctx, "blocks/frame: %d (code=%d)\n", s->num_blocks, s->num_blks_code);
    if (s->cutoff)
        ff_dlog(avctx, "cutoff: %d\n", s->cutoff);

    ff_dlog(avctx, "per_frame_metadata: %s\n",
            opt->allow_per_frame_metadata?"on":"off");
    if (s->has_center)
        ff_dlog(avctx, "center_mixlev: %0.3f (%d)\n", opt->center_mix_level,
                s->center_mix_level);
    else
        ff_dlog(avctx, "center_mixlev: {not written}\n");
    if (s->has_surround)
        ff_dlog(avctx, "surround_mixlev: %0.3f (%d)\n", opt->surround_mix_level,
                s->surround_mix_level);
    else
        ff_dlog(avctx, "surround_mixlev: {not written}\n");
    if (opt->audio_production_info) {
        ff_dlog(avctx, "mixing_level: %ddB\n", opt->mixing_level);
        switch (opt->room_type) {
        case AC3ENC_OPT_NOT_INDICATED: av_strlcpy(strbuf, "notindicated", 32); break;
        case AC3ENC_OPT_LARGE_ROOM:    av_strlcpy(strbuf, "large", 32);        break;
        case AC3ENC_OPT_SMALL_ROOM:    av_strlcpy(strbuf, "small", 32);        break;
        default: snprintf(strbuf, 32, "ERROR (%d)", opt->room_type);
        }
        ff_dlog(avctx, "room_type: %s\n", strbuf);
    } else {
        ff_dlog(avctx, "mixing_level: {not written}\n");
        ff_dlog(avctx, "room_type: {not written}\n");
    }
    ff_dlog(avctx, "copyright: %s\n", opt->copyright?"on":"off");
    ff_dlog(avctx, "dialnorm: %ddB\n", opt->dialogue_level);
    if (s->channel_mode == AC3_CHMODE_STEREO) {
        switch (opt->dolby_surround_mode) {
        case AC3ENC_OPT_NOT_INDICATED: av_strlcpy(strbuf, "notindicated", 32); break;
        case AC3ENC_OPT_MODE_ON:       av_strlcpy(strbuf, "on", 32);           break;
        case AC3ENC_OPT_MODE_OFF:      av_strlcpy(strbuf, "off", 32);          break;
        default: snprintf(strbuf, 32, "ERROR (%d)", opt->dolby_surround_mode);
        }
        ff_dlog(avctx, "dsur_mode: %s\n", strbuf);
    } else {
        ff_dlog(avctx, "dsur_mode: {not written}\n");
    }
    ff_dlog(avctx, "original: %s\n", opt->original?"on":"off");

    if (s->bitstream_id == 6) {
        if (opt->extended_bsi_1) {
            switch (opt->preferred_stereo_downmix) {
            case AC3ENC_OPT_NOT_INDICATED: av_strlcpy(strbuf, "notindicated", 32); break;
            case AC3ENC_OPT_DOWNMIX_LTRT:  av_strlcpy(strbuf, "ltrt", 32);         break;
            case AC3ENC_OPT_DOWNMIX_LORO:  av_strlcpy(strbuf, "loro", 32);         break;
            default: snprintf(strbuf, 32, "ERROR (%d)", opt->preferred_stereo_downmix);
            }
            ff_dlog(avctx, "dmix_mode: %s\n", strbuf);
            ff_dlog(avctx, "ltrt_cmixlev: %0.3f (%d)\n",
                    opt->ltrt_center_mix_level, s->ltrt_center_mix_level);
            ff_dlog(avctx, "ltrt_surmixlev: %0.3f (%d)\n",
                    opt->ltrt_surround_mix_level, s->ltrt_surround_mix_level);
            ff_dlog(avctx, "loro_cmixlev: %0.3f (%d)\n",
                    opt->loro_center_mix_level, s->loro_center_mix_level);
            ff_dlog(avctx, "loro_surmixlev: %0.3f (%d)\n",
                    opt->loro_surround_mix_level, s->loro_surround_mix_level);
        } else {
            ff_dlog(avctx, "extended bitstream info 1: {not written}\n");
        }
        if (opt->extended_bsi_2) {
            switch (opt->dolby_surround_ex_mode) {
            case AC3ENC_OPT_NOT_INDICATED: av_strlcpy(strbuf, "notindicated", 32); break;
            case AC3ENC_OPT_MODE_ON:       av_strlcpy(strbuf, "on", 32);           break;
            case AC3ENC_OPT_MODE_OFF:      av_strlcpy(strbuf, "off", 32);          break;
            default: snprintf(strbuf, 32, "ERROR (%d)", opt->dolby_surround_ex_mode);
            }
            ff_dlog(avctx, "dsurex_mode: %s\n", strbuf);
            switch (opt->dolby_headphone_mode) {
            case AC3ENC_OPT_NOT_INDICATED: av_strlcpy(strbuf, "notindicated", 32); break;
            case AC3ENC_OPT_MODE_ON:       av_strlcpy(strbuf, "on", 32);           break;
            case AC3ENC_OPT_MODE_OFF:      av_strlcpy(strbuf, "off", 32);          break;
            default: snprintf(strbuf, 32, "ERROR (%d)", opt->dolby_headphone_mode);
            }
            ff_dlog(avctx, "dheadphone_mode: %s\n", strbuf);

            switch (opt->ad_converter_type) {
            case AC3ENC_OPT_ADCONV_STANDARD: av_strlcpy(strbuf, "standard", 32); break;
            case AC3ENC_OPT_ADCONV_HDCD:     av_strlcpy(strbuf, "hdcd", 32);     break;
            default: snprintf(strbuf, 32, "ERROR (%d)", opt->ad_converter_type);
            }
            ff_dlog(avctx, "ad_conv_type: %s\n", strbuf);
        } else {
            ff_dlog(avctx, "extended bitstream info 2: {not written}\n");
        }
    }
#endif
}