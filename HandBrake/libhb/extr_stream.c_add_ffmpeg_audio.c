#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {int /*<<< orphan*/  iso639_2; } ;
typedef  TYPE_9__ iso639_lang_t ;
struct TYPE_25__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_10__ hb_title_t ;
struct TYPE_26__ {TYPE_1__* ffmpeg_ic; } ;
typedef  TYPE_11__ hb_stream_t ;
struct TYPE_32__ {int num; int den; } ;
struct TYPE_37__ {int track; int codec_param; int /*<<< orphan*/  name; int /*<<< orphan*/  codec; TYPE_2__ timebase; int /*<<< orphan*/  encoder_delay; scalar_t__ bitrate; } ;
struct TYPE_36__ {int /*<<< orphan*/  attributes; } ;
struct TYPE_38__ {TYPE_7__ in; TYPE_6__ lang; } ;
struct TYPE_33__ {int length; int /*<<< orphan*/  bytes; } ;
struct TYPE_34__ {TYPE_3__ extradata; } ;
struct TYPE_35__ {TYPE_4__ config; } ;
struct TYPE_27__ {int id; TYPE_8__ config; TYPE_5__ priv; } ;
typedef  TYPE_12__ hb_audio_t ;
struct TYPE_31__ {TYPE_13__** streams; } ;
struct TYPE_30__ {int codec_id; int /*<<< orphan*/  extradata; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  profile; int /*<<< orphan*/  initial_padding; } ;
struct TYPE_29__ {char* value; } ;
struct TYPE_28__ {int disposition; int /*<<< orphan*/  metadata; TYPE_15__* codecpar; } ;
typedef  TYPE_13__ AVStream ;
typedef  TYPE_14__ AVDictionaryEntry ;
typedef  TYPE_15__ AVCodecParameters ;

/* Variables and functions */
#define  AV_CODEC_ID_AAC 139 
#define  AV_CODEC_ID_AC3 138 
#define  AV_CODEC_ID_DTS 137 
#define  AV_CODEC_ID_EAC3 136 
#define  AV_CODEC_ID_FLAC 135 
#define  AV_CODEC_ID_MP3 134 
#define  AV_CODEC_ID_TRUEHD 133 
 int AV_DISPOSITION_DEFAULT ; 
#define  FF_PROFILE_DTS 132 
#define  FF_PROFILE_DTS_96_24 131 
#define  FF_PROFILE_DTS_ES 130 
#define  FF_PROFILE_DTS_HD_HRA 129 
#define  FF_PROFILE_DTS_HD_MA 128 
 int /*<<< orphan*/  HB_ACODEC_AC3 ; 
 int /*<<< orphan*/  HB_ACODEC_DCA ; 
 int /*<<< orphan*/  HB_ACODEC_DCA_HD ; 
 int /*<<< orphan*/  HB_ACODEC_FFAAC ; 
 int /*<<< orphan*/  HB_ACODEC_FFEAC3 ; 
 int /*<<< orphan*/  HB_ACODEC_FFFLAC ; 
 int /*<<< orphan*/  HB_ACODEC_FFMPEG ; 
 int /*<<< orphan*/  HB_ACODEC_FFTRUEHD ; 
 int /*<<< orphan*/  HB_ACODEC_MP3 ; 
 int /*<<< orphan*/  HB_AUDIO_ATTR_DEFAULT ; 
 int /*<<< orphan*/  HB_CONFIG_MAX_SIZE ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_14__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_12__* calloc (int,int) ; 
 char* ffmpeg_track_name (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_12__*) ; 
 TYPE_9__* lang_for_code2 (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_audio_description (TYPE_12__*,TYPE_9__*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void add_ffmpeg_audio(hb_title_t *title, hb_stream_t *stream, int id)
{
    AVStream *st                = stream->ffmpeg_ic->streams[id];
    AVCodecParameters * codecpar = st->codecpar;
    AVDictionaryEntry * tag_lang = av_dict_get(st->metadata, "language", NULL, 0);
    iso639_lang_t     * lang = lang_for_code2(tag_lang != NULL ?
                                              tag_lang->value : "und");
    const char        * name = ffmpeg_track_name(st, lang->iso639_2);

    hb_audio_t *audio              = calloc(1, sizeof(*audio));
    audio->id                      = id;
    audio->config.in.track         = id;
    audio->config.in.codec         = HB_ACODEC_FFMPEG;
    audio->config.in.codec_param   = codecpar->codec_id;
    // set the bitrate to 0; decavcodecaBSInfo will be called and fill the rest
    audio->config.in.bitrate       = 0;
    audio->config.in.encoder_delay = codecpar->initial_padding;

    // If we ever improve our pipeline to allow other time bases...
    // audio->config.in.timebase.num  = st->time_base.num;
    // audio->config.in.timebase.den  = st->time_base.den;
    audio->config.in.timebase.num  = 1;
    audio->config.in.timebase.den  = 90000;

    // set the input codec and extradata for Passthru
    switch (codecpar->codec_id)
    {
        case AV_CODEC_ID_AAC:
        {
            int len = MIN(codecpar->extradata_size, HB_CONFIG_MAX_SIZE);
            memcpy(audio->priv.config.extradata.bytes, codecpar->extradata, len);
            audio->priv.config.extradata.length = len;
            audio->config.in.codec              = HB_ACODEC_FFAAC;
        } break;

        case AV_CODEC_ID_AC3:
            audio->config.in.codec       = HB_ACODEC_AC3;
            break;

        case AV_CODEC_ID_EAC3:
            audio->config.in.codec = HB_ACODEC_FFEAC3;
            break;

        case AV_CODEC_ID_TRUEHD:
            audio->config.in.codec = HB_ACODEC_FFTRUEHD;
            break;

        case AV_CODEC_ID_DTS:
        {
            switch (codecpar->profile)
            {
                case FF_PROFILE_DTS:
                case FF_PROFILE_DTS_ES:
                case FF_PROFILE_DTS_96_24:
                    audio->config.in.codec = HB_ACODEC_DCA;
                    break;

                case FF_PROFILE_DTS_HD_MA:
                case FF_PROFILE_DTS_HD_HRA:
                    audio->config.in.codec = HB_ACODEC_DCA_HD;
                    break;

                default:
                    break;
            }
        } break;

        case AV_CODEC_ID_FLAC:
        {
            int len = MIN(codecpar->extradata_size, HB_CONFIG_MAX_SIZE);
            memcpy(audio->priv.config.extradata.bytes, codecpar->extradata, len);
            audio->priv.config.extradata.length = len;
            audio->config.in.codec              = HB_ACODEC_FFFLAC;
        } break;

        case AV_CODEC_ID_MP3:
            audio->config.in.codec = HB_ACODEC_MP3;
            break;

        default:
            break;
    }

    if (st->disposition & AV_DISPOSITION_DEFAULT)
    {
        audio->config.lang.attributes |= HB_AUDIO_ATTR_DEFAULT;
    }

    set_audio_description(audio, lang);
    if (name != NULL)
    {
        audio->config.in.name = strdup(name);
    }
    hb_list_add(title->list_audio, audio);
}