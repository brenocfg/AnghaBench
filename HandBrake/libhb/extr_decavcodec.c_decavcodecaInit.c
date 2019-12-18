#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_45__ {int /*<<< orphan*/ * frame; TYPE_6__* audio; TYPE_16__* context; int /*<<< orphan*/ * resample; int /*<<< orphan*/  parser; TYPE_3__* title; int /*<<< orphan*/  list; scalar_t__ next_pts; int /*<<< orphan*/  drop_samples; TYPE_11__* job; } ;
typedef  TYPE_9__ hb_work_private_t ;
struct TYPE_30__ {int codec_param; TYPE_6__* audio; TYPE_3__* title; TYPE_9__* private_data; } ;
typedef  TYPE_10__ hb_work_object_t ;
struct TYPE_31__ {TYPE_3__* title; } ;
typedef  TYPE_11__ hb_job_t ;
typedef  int /*<<< orphan*/  drc_scale ;
struct TYPE_44__ {int codec; int mixdown; float dynamic_range_compression; int /*<<< orphan*/  track; int /*<<< orphan*/  normalize_mix_level; } ;
struct TYPE_38__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_41__ {scalar_t__ channel_layout; TYPE_2__ timebase; int /*<<< orphan*/  codec_param; int /*<<< orphan*/  codec; int /*<<< orphan*/  samplerate; int /*<<< orphan*/  encoder_delay; } ;
struct TYPE_43__ {TYPE_5__ in; TYPE_8__ out; } ;
struct TYPE_42__ {size_t id; TYPE_7__ config; } ;
struct TYPE_40__ {int /*<<< orphan*/  codecpar; } ;
struct TYPE_39__ {int /*<<< orphan*/ * opaque_priv; } ;
struct TYPE_37__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_36__ {int codec_id; TYPE_1__ pkt_timebase; int /*<<< orphan*/  request_channel_layout; } ;
struct TYPE_35__ {int /*<<< orphan*/ * priv_class; } ;
struct TYPE_34__ {int /*<<< orphan*/  key; } ;
struct TYPE_33__ {TYPE_4__** streams; } ;
struct TYPE_32__ {float max; } ;
typedef  TYPE_12__ AVOption ;
typedef  TYPE_13__ AVFormatContext ;
typedef  TYPE_14__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_15__ AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CH_LAYOUT_5POINT1 ; 
 scalar_t__ AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
#define  AV_CODEC_ID_AC3 133 
#define  AV_CODEC_ID_DTS 132 
#define  AV_CODEC_ID_EAC3 131 
#define  AV_CODEC_ID_TRUEHD 130 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_OPT_FLAG_AUDIO_PARAM ; 
 int AV_OPT_FLAG_DECODING_PARAM ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_FAKE_OBJ ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLT ; 
 int HB_ACODEC_PASS_FLAG ; 
#define  HB_AMIXDOWN_DOLBY 129 
#define  HB_AMIXDOWN_DOLBYPLII 128 
 int HB_AMIXDOWN_MONO ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_14__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 TYPE_12__* av_opt_find2 (void*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_parser_init (int) ; 
 TYPE_16__* avcodec_alloc_context3 (TYPE_15__*) ; 
 TYPE_15__* avcodec_find_decoder (int) ; 
 int /*<<< orphan*/  avcodec_parameters_to_context (TYPE_16__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* calloc (int,int) ; 
 scalar_t__ hb_audio_can_apply_drc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_audio_resample_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hb_avcodec_open (TYPE_16__*,TYPE_15__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_ff_mixdown_xlat (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_ff_set_sample_fmt (TYPE_16__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float) ; 

__attribute__((used)) static int decavcodecaInit( hb_work_object_t * w, hb_job_t * job )
{
    AVCodec * codec;

    hb_work_private_t * pv = calloc( 1, sizeof( hb_work_private_t ) );
    w->private_data = pv;

    pv->job          = job;
    pv->audio        = w->audio;
    pv->drop_samples = w->audio->config.in.encoder_delay;
    pv->next_pts     = (int64_t)AV_NOPTS_VALUE;
    if (job)
        pv->title    = job->title;
    else
        pv->title    = w->title;
    hb_buffer_list_clear(&pv->list);

    codec       = avcodec_find_decoder(w->codec_param);
    pv->context = avcodec_alloc_context3(codec);

    if (pv->title->opaque_priv != NULL)
    {
        AVFormatContext *ic = (AVFormatContext*)pv->title->opaque_priv;
        avcodec_parameters_to_context(pv->context,
                                      ic->streams[w->audio->id]->codecpar);
        // libav's eac3 parser toggles the codec_id in the context as
        // it reads eac3 data between AV_CODEC_ID_AC3 and AV_CODEC_ID_EAC3.
        // It detects an AC3 sync pattern sometimes in ac3_sync() which
        // causes it to eventually set avctx->codec_id to AV_CODEC_ID_AC3
        // in ff_aac_ac3_parse(). Since we are parsing some data before
        // we get here, the codec_id may have flipped.  This will cause an
        // error in hb_avcodec_open().  So flip it back!
        pv->context->codec_id = w->codec_param;
    }
    else
    {
        pv->parser = av_parser_init(w->codec_param);
    }
    hb_ff_set_sample_fmt(pv->context, codec, AV_SAMPLE_FMT_FLT);

    /* Downmixing & sample_fmt conversion */
    if (!(w->audio->config.out.codec & HB_ACODEC_PASS_FLAG))
    {
        // Currently, samplerate conversion is performed in sync.c
        // So set output samplerate to input samplerate
        // This should someday get reworked to be part of an audio
        // filter pipleine.
        pv->resample =
            hb_audio_resample_init(AV_SAMPLE_FMT_FLT,
                                   w->audio->config.in.samplerate,
                                   w->audio->config.out.mixdown,
                                   w->audio->config.out.normalize_mix_level);
        if (pv->resample == NULL)
        {
            hb_error("decavcodecaInit: hb_audio_resample_init() failed");
            return 1;
        }
        /*
         * Some audio decoders can downmix using embedded coefficients,
         * or dedicated audio substreams for a specific channel layout.
         *
         * But some will e.g. use normalized mix coefficients unconditionally,
         * so we need to make sure this matches what the user actually requested.
         */
        int avcodec_downmix = 0;
        switch (w->codec_param)
        {
            case AV_CODEC_ID_AC3:
            case AV_CODEC_ID_EAC3:
                avcodec_downmix = w->audio->config.out.normalize_mix_level != 0;
                break;
            case AV_CODEC_ID_DTS:
                avcodec_downmix = w->audio->config.out.normalize_mix_level == 0;
                break;
            case AV_CODEC_ID_TRUEHD:
                avcodec_downmix = (w->audio->config.out.normalize_mix_level == 0     ||
                                   w->audio->config.out.mixdown == HB_AMIXDOWN_MONO  ||
                                   w->audio->config.out.mixdown == HB_AMIXDOWN_DOLBY ||
                                   w->audio->config.out.mixdown == HB_AMIXDOWN_DOLBYPLII);
                break;
            default:
                break;
        }
        if (avcodec_downmix)
        {
            switch (w->audio->config.out.mixdown)
            {
                // request 5.1 before downmixing to dpl1/dpl2
                case HB_AMIXDOWN_DOLBY:
                case HB_AMIXDOWN_DOLBYPLII:
                    pv->context->request_channel_layout = AV_CH_LAYOUT_5POINT1;
                    break;
                // request the layout corresponding to the selected mixdown
                default:
                    pv->context->request_channel_layout =
                        hb_ff_mixdown_xlat(w->audio->config.out.mixdown, NULL);
                    break;
            }
        }
    }

    // libavcodec can't decode TrueHD Mono (bug #356)
    // work around it by requesting Stereo and downmixing
    if (w->codec_param                     == AV_CODEC_ID_TRUEHD &&
        w->audio->config.in.channel_layout == AV_CH_LAYOUT_MONO)
    {
        pv->context->request_channel_layout = AV_CH_LAYOUT_STEREO;
    }

    // Set decoder opts...
    AVDictionary * av_opts = NULL;
    av_dict_set( &av_opts, "refcounted_frames", "1", 0 );

    // Dynamic Range Compression
    if (w->audio->config.out.dynamic_range_compression >= 0.0f &&
        hb_audio_can_apply_drc(w->audio->config.in.codec,
                               w->audio->config.in.codec_param, 0))
    {
        float drc_scale_max = 1.0f;
        /*
         * avcodec_open will fail if the value for any of the options is out of
         * range, so assume a conservative maximum of 1 and try to determine the
         * option's actual upper limit.
         */
        if (codec != NULL && codec->priv_class != NULL)
        {
            const AVOption *opt;
            opt = av_opt_find2((void*)&codec->priv_class, "drc_scale", NULL,
                               AV_OPT_FLAG_DECODING_PARAM|AV_OPT_FLAG_AUDIO_PARAM,
                               AV_OPT_SEARCH_FAKE_OBJ, NULL);
            if (opt != NULL)
            {
                drc_scale_max = opt->max;
            }
        }
        if (w->audio->config.out.dynamic_range_compression > drc_scale_max)
        {
            hb_log("decavcodecaInit: track %d, sanitizing out-of-range DRC %.2f to %.2f",
                   w->audio->config.out.track,
                   w->audio->config.out.dynamic_range_compression, drc_scale_max);
            w->audio->config.out.dynamic_range_compression = drc_scale_max;
        }

        char drc_scale[5]; // "?.??\n"
        snprintf(drc_scale, sizeof(drc_scale), "%.2f",
                 w->audio->config.out.dynamic_range_compression);
        av_dict_set(&av_opts, "drc_scale", drc_scale, 0);
    }

    if (hb_avcodec_open(pv->context, codec, &av_opts, 0))
    {
        av_dict_free( &av_opts );
        hb_log("decavcodecaInit: avcodec_open failed");
        return 1;
    }
    pv->context->pkt_timebase.num = pv->audio->config.in.timebase.num;
    pv->context->pkt_timebase.den = pv->audio->config.in.timebase.den;

    // avcodec_open populates av_opts with the things it didn't recognize.
    AVDictionaryEntry *t = NULL;
    while ((t = av_dict_get(av_opts, "", t, AV_DICT_IGNORE_SUFFIX)) != NULL)
    {
            hb_log("decavcodecaInit: unknown option '%s'", t->key);
    }
    av_dict_free( &av_opts );

    pv->frame = av_frame_alloc();
    if (pv->frame == NULL)
    {
        hb_log("decavcodecaInit: av_frame_alloc failed");
        return 1;
    }

    return 0;
}