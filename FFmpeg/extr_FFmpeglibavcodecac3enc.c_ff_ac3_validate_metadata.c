#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int audio_production_info; int extended_bsi_1; int extended_bsi_2; int eac3_mixing_metadata; int eac3_info_metadata; scalar_t__ preferred_stereo_downmix; scalar_t__ ltrt_center_mix_level; scalar_t__ loro_center_mix_level; scalar_t__ ltrt_surround_mix_level; scalar_t__ loro_surround_mix_level; scalar_t__ copyright; scalar_t__ original; scalar_t__ dolby_headphone_mode; scalar_t__ dolby_surround_mode; scalar_t__ dolby_surround_ex_mode; scalar_t__ mixing_level; scalar_t__ room_type; scalar_t__ ad_converter_type; scalar_t__ center_mix_level; scalar_t__ surround_mix_level; } ;
struct TYPE_8__ {scalar_t__ channel_mode; int bitstream_id; scalar_t__ eac3; int /*<<< orphan*/  loro_surround_mix_level; int /*<<< orphan*/  ltrt_surround_mix_level; scalar_t__ has_surround; int /*<<< orphan*/  loro_center_mix_level; int /*<<< orphan*/  ltrt_center_mix_level; scalar_t__ has_center; int /*<<< orphan*/  surround_mix_level; int /*<<< orphan*/  center_mix_level; TYPE_3__ options; TYPE_1__* avctx; } ;
struct TYPE_7__ {scalar_t__ audio_service_type; int channels; } ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ AC3EncodeContext ;
typedef  TYPE_3__ AC3EncOptions ;

/* Variables and functions */
 scalar_t__ AC3ENC_OPT_ADCONV_STANDARD ; 
 scalar_t__ AC3ENC_OPT_NONE ; 
 void* AC3ENC_OPT_NOT_INDICATED ; 
 scalar_t__ AC3ENC_OPT_OFF ; 
 scalar_t__ AC3ENC_OPT_ON ; 
 scalar_t__ AC3_CHMODE_2F2R ; 
 scalar_t__ AC3_CHMODE_STEREO ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_AUDIO_SERVICE_TYPE_COMMENTARY ; 
 scalar_t__ AV_AUDIO_SERVICE_TYPE_EMERGENCY ; 
 scalar_t__ AV_AUDIO_SERVICE_TYPE_KARAOKE ; 
 scalar_t__ AV_AUDIO_SERVICE_TYPE_MAIN ; 
 scalar_t__ AV_AUDIO_SERVICE_TYPE_VOICE_OVER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  CMIXLEV_NUM_OPTIONS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EXTMIXLEV_NUM_OPTIONS ; 
 int /*<<< orphan*/  SURMIXLEV_NUM_OPTIONS ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmixlev_options ; 
 int /*<<< orphan*/  extmixlev_options ; 
 int /*<<< orphan*/  surmixlev_options ; 
 int /*<<< orphan*/  validate_mix_level (TYPE_1__*,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int ff_ac3_validate_metadata(AC3EncodeContext *s)
{
    AVCodecContext *avctx = s->avctx;
    AC3EncOptions *opt = &s->options;

    opt->audio_production_info = 0;
    opt->extended_bsi_1        = 0;
    opt->extended_bsi_2        = 0;
    opt->eac3_mixing_metadata  = 0;
    opt->eac3_info_metadata    = 0;

    /* determine mixing metadata / xbsi1 use */
    if (s->channel_mode > AC3_CHMODE_STEREO && opt->preferred_stereo_downmix != AC3ENC_OPT_NONE) {
        opt->extended_bsi_1       = 1;
        opt->eac3_mixing_metadata = 1;
    }
    if (s->has_center &&
        (opt->ltrt_center_mix_level >= 0 || opt->loro_center_mix_level >= 0)) {
        opt->extended_bsi_1       = 1;
        opt->eac3_mixing_metadata = 1;
    }
    if (s->has_surround &&
        (opt->ltrt_surround_mix_level >= 0 || opt->loro_surround_mix_level >= 0)) {
        opt->extended_bsi_1       = 1;
        opt->eac3_mixing_metadata = 1;
    }

    if (s->eac3) {
        /* determine info metadata use */
        if (avctx->audio_service_type != AV_AUDIO_SERVICE_TYPE_MAIN)
            opt->eac3_info_metadata = 1;
        if (opt->copyright != AC3ENC_OPT_NONE || opt->original != AC3ENC_OPT_NONE)
            opt->eac3_info_metadata = 1;
        if (s->channel_mode == AC3_CHMODE_STEREO &&
            (opt->dolby_headphone_mode != AC3ENC_OPT_NONE || opt->dolby_surround_mode != AC3ENC_OPT_NONE))
            opt->eac3_info_metadata = 1;
        if (s->channel_mode >= AC3_CHMODE_2F2R && opt->dolby_surround_ex_mode != AC3ENC_OPT_NONE)
            opt->eac3_info_metadata = 1;
        if (opt->mixing_level != AC3ENC_OPT_NONE || opt->room_type != AC3ENC_OPT_NONE ||
            opt->ad_converter_type != AC3ENC_OPT_NONE) {
            opt->audio_production_info = 1;
            opt->eac3_info_metadata    = 1;
        }
    } else {
        /* determine audio production info use */
        if (opt->mixing_level != AC3ENC_OPT_NONE || opt->room_type != AC3ENC_OPT_NONE)
            opt->audio_production_info = 1;

        /* determine xbsi2 use */
        if (s->channel_mode >= AC3_CHMODE_2F2R && opt->dolby_surround_ex_mode != AC3ENC_OPT_NONE)
            opt->extended_bsi_2 = 1;
        if (s->channel_mode == AC3_CHMODE_STEREO && opt->dolby_headphone_mode != AC3ENC_OPT_NONE)
            opt->extended_bsi_2 = 1;
        if (opt->ad_converter_type != AC3ENC_OPT_NONE)
            opt->extended_bsi_2 = 1;
    }

    /* validate AC-3 mixing levels */
    if (!s->eac3) {
        if (s->has_center) {
            validate_mix_level(avctx, "center_mix_level", &opt->center_mix_level,
                            cmixlev_options, CMIXLEV_NUM_OPTIONS, 1, 0,
                            &s->center_mix_level);
        }
        if (s->has_surround) {
            validate_mix_level(avctx, "surround_mix_level", &opt->surround_mix_level,
                            surmixlev_options, SURMIXLEV_NUM_OPTIONS, 1, 0,
                            &s->surround_mix_level);
        }
    }

    /* validate extended bsi 1 / mixing metadata */
    if (opt->extended_bsi_1 || opt->eac3_mixing_metadata) {
        /* default preferred stereo downmix */
        if (opt->preferred_stereo_downmix == AC3ENC_OPT_NONE)
            opt->preferred_stereo_downmix = AC3ENC_OPT_NOT_INDICATED;
        if (!s->eac3 || s->has_center) {
            /* validate Lt/Rt center mix level */
            validate_mix_level(avctx, "ltrt_center_mix_level",
                               &opt->ltrt_center_mix_level, extmixlev_options,
                               EXTMIXLEV_NUM_OPTIONS, 5, 0,
                               &s->ltrt_center_mix_level);
            /* validate Lo/Ro center mix level */
            validate_mix_level(avctx, "loro_center_mix_level",
                               &opt->loro_center_mix_level, extmixlev_options,
                               EXTMIXLEV_NUM_OPTIONS, 5, 0,
                               &s->loro_center_mix_level);
        }
        if (!s->eac3 || s->has_surround) {
            /* validate Lt/Rt surround mix level */
            validate_mix_level(avctx, "ltrt_surround_mix_level",
                               &opt->ltrt_surround_mix_level, extmixlev_options,
                               EXTMIXLEV_NUM_OPTIONS, 6, 3,
                               &s->ltrt_surround_mix_level);
            /* validate Lo/Ro surround mix level */
            validate_mix_level(avctx, "loro_surround_mix_level",
                               &opt->loro_surround_mix_level, extmixlev_options,
                               EXTMIXLEV_NUM_OPTIONS, 6, 3,
                               &s->loro_surround_mix_level);
        }
    }

    /* validate audio service type / channels combination */
    if ((avctx->audio_service_type == AV_AUDIO_SERVICE_TYPE_KARAOKE &&
         avctx->channels == 1) ||
        ((avctx->audio_service_type == AV_AUDIO_SERVICE_TYPE_COMMENTARY ||
          avctx->audio_service_type == AV_AUDIO_SERVICE_TYPE_EMERGENCY  ||
          avctx->audio_service_type == AV_AUDIO_SERVICE_TYPE_VOICE_OVER)
         && avctx->channels > 1)) {
        av_log(avctx, AV_LOG_ERROR, "invalid audio service type for the "
                                    "specified number of channels\n");
        return AVERROR(EINVAL);
    }

    /* validate extended bsi 2 / info metadata */
    if (opt->extended_bsi_2 || opt->eac3_info_metadata) {
        /* default dolby headphone mode */
        if (opt->dolby_headphone_mode == AC3ENC_OPT_NONE)
            opt->dolby_headphone_mode = AC3ENC_OPT_NOT_INDICATED;
        /* default dolby surround ex mode */
        if (opt->dolby_surround_ex_mode == AC3ENC_OPT_NONE)
            opt->dolby_surround_ex_mode = AC3ENC_OPT_NOT_INDICATED;
        /* default A/D converter type */
        if (opt->ad_converter_type == AC3ENC_OPT_NONE)
            opt->ad_converter_type = AC3ENC_OPT_ADCONV_STANDARD;
    }

    /* copyright & original defaults */
    if (!s->eac3 || opt->eac3_info_metadata) {
        /* default copyright */
        if (opt->copyright == AC3ENC_OPT_NONE)
            opt->copyright = AC3ENC_OPT_OFF;
        /* default original */
        if (opt->original == AC3ENC_OPT_NONE)
            opt->original = AC3ENC_OPT_ON;
    }

    /* dolby surround mode default */
    if (!s->eac3 || opt->eac3_info_metadata) {
        if (opt->dolby_surround_mode == AC3ENC_OPT_NONE)
            opt->dolby_surround_mode = AC3ENC_OPT_NOT_INDICATED;
    }

    /* validate audio production info */
    if (opt->audio_production_info) {
        if (opt->mixing_level == AC3ENC_OPT_NONE) {
            av_log(avctx, AV_LOG_ERROR, "mixing_level must be set if "
                   "room_type is set\n");
            return AVERROR(EINVAL);
        }
        if (opt->mixing_level < 80) {
            av_log(avctx, AV_LOG_ERROR, "invalid mixing level. must be between "
                   "80dB and 111dB\n");
            return AVERROR(EINVAL);
        }
        /* default room type */
        if (opt->room_type == AC3ENC_OPT_NONE)
            opt->room_type = AC3ENC_OPT_NOT_INDICATED;
    }

    /* set bitstream id for alternate bitstream syntax */
    if (!s->eac3 && (opt->extended_bsi_1 || opt->extended_bsi_2)) {
        if (s->bitstream_id > 8 && s->bitstream_id < 11) {
            static int warn_once = 1;
            if (warn_once) {
                av_log(avctx, AV_LOG_WARNING, "alternate bitstream syntax is "
                       "not compatible with reduced samplerates. writing of "
                       "extended bitstream information will be disabled.\n");
                warn_once = 0;
            }
        } else {
            s->bitstream_id = 6;
        }
    }

    return 0;
}