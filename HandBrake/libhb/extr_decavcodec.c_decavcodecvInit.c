#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_37__ {scalar_t__ io_pattern; int usage_threaded; int additional_buffers; scalar_t__ sync_need; int /*<<< orphan*/  async_depth; int /*<<< orphan*/  impl_requested; } ;
struct TYPE_38__ {scalar_t__ decode; TYPE_4__ config; int /*<<< orphan*/  codec_name; } ;
struct TYPE_42__ {int video_codec_opened; int /*<<< orphan*/ * list_subtitle; int /*<<< orphan*/ * frame; int /*<<< orphan*/  parser; TYPE_8__* title; TYPE_21__* context; int /*<<< orphan*/  threads; int /*<<< orphan*/ * codec; TYPE_5__ qsv; TYPE_13__* job; int /*<<< orphan*/  list; scalar_t__ next_pts; } ;
typedef  TYPE_9__ hb_work_private_t ;
struct TYPE_27__ {int /*<<< orphan*/  codec_param; TYPE_8__* title; TYPE_9__* private_data; } ;
typedef  TYPE_10__ hb_work_object_t ;
struct TYPE_28__ {scalar_t__ source; scalar_t__ id; } ;
typedef  TYPE_11__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_qsv_space ;
struct TYPE_29__ {int capabilities; int /*<<< orphan*/  implementation; } ;
typedef  TYPE_12__ hb_qsv_info_t ;
typedef  int /*<<< orphan*/  hb_qsv_context ;
struct TYPE_40__ {TYPE_18__* ctx; int /*<<< orphan*/  async_depth; } ;
struct TYPE_30__ {int /*<<< orphan*/  list_subtitle; TYPE_8__* title; TYPE_7__ qsv; int /*<<< orphan*/  vcodec; } ;
typedef  TYPE_13__ hb_job_t ;
struct TYPE_36__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_41__ {int flags; size_t video_id; TYPE_3__ video_timebase; scalar_t__ opaque_priv; int /*<<< orphan*/  has_resolution_change; } ;
struct TYPE_39__ {int is_init_done; } ;
struct TYPE_35__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_34__ {int error_concealment; scalar_t__ codec_id; TYPE_2__ pkt_timebase; scalar_t__ hwaccel_context; int /*<<< orphan*/  get_buffer2; int /*<<< orphan*/  get_format; int /*<<< orphan*/  err_recognition; int /*<<< orphan*/  workaround_bugs; } ;
struct TYPE_33__ {int /*<<< orphan*/  codecpar; } ;
struct TYPE_32__ {TYPE_6__* dec_space; } ;
struct TYPE_31__ {TYPE_1__** streams; } ;
typedef  TYPE_14__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_HEVC ; 
 int /*<<< orphan*/  AV_EF_CRCCHECK ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ CC608SUB ; 
 int /*<<< orphan*/  FF_BUG_AUTODETECT ; 
 int FF_EC_DEBLOCK ; 
 int FF_EC_GUESS_MVS ; 
 int HBTF_NO_IDR ; 
 int HBTF_RAW_VIDEO ; 
 int /*<<< orphan*/  HB_FFMPEG_THREADS_AUTO ; 
 int HB_QSV_CAP_RATECONTROL_LA ; 
 scalar_t__ HB_SUBTITLE_EMBEDDED_CC_TAG ; 
 scalar_t__ MFX_IOPATTERN_OUT_SYSTEM_MEMORY ; 
 scalar_t__ MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_parser_init (int /*<<< orphan*/ ) ; 
 TYPE_21__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avcodec_find_decoder_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_parameters_to_context (TYPE_21__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* calloc (int,int) ; 
 scalar_t__ hb_avcodec_open (TYPE_21__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ *,TYPE_11__*) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_list_init () ; 
 TYPE_11__* hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  hb_qsv_add_context_usage (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_qsv_decode_get_codec_name (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_qsv_decode_is_enabled (TYPE_13__*) ; 
 scalar_t__ hb_qsv_full_path_is_enabled (TYPE_13__*) ; 
 int /*<<< orphan*/  hb_qsv_get_buffer ; 
 int /*<<< orphan*/  hb_qsv_get_format ; 
 TYPE_12__* hb_qsv_info_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decavcodecvInit( hb_work_object_t * w, hb_job_t * job )
{

    hb_work_private_t *pv = calloc( 1, sizeof( hb_work_private_t ) );

    w->private_data = pv;
    pv->job         = job;
    pv->next_pts    = (int64_t)AV_NOPTS_VALUE;
    if ( job )
        pv->title = job->title;
    else
        pv->title = w->title;
    if (pv->title->flags & HBTF_RAW_VIDEO)
        pv->next_pts = 0;
    hb_buffer_list_clear(&pv->list);

#if HB_PROJECT_FEATURE_QSV
    if ((pv->qsv.decode = hb_qsv_decode_is_enabled(job)))
    {
        pv->qsv.codec_name = hb_qsv_decode_get_codec_name(w->codec_param);
        pv->qsv.config.io_pattern = MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
        if(hb_qsv_full_path_is_enabled(job))
        {
            hb_qsv_info_t *info = hb_qsv_info_get(job->vcodec);
            if (info != NULL)
            {
                // setup the QSV configuration
                pv->qsv.config.io_pattern         = MFX_IOPATTERN_OUT_VIDEO_MEMORY;
                pv->qsv.config.impl_requested     = info->implementation;
                pv->qsv.config.async_depth        = job->qsv.async_depth;
                pv->qsv.config.sync_need          =  0;
                pv->qsv.config.usage_threaded     =  1;
                pv->qsv.config.additional_buffers = 64; // FIFO_LARGE
                if (info->capabilities & HB_QSV_CAP_RATECONTROL_LA)
                {
                    // more surfaces may be needed for the lookahead
                    pv->qsv.config.additional_buffers = 160;
                }
                if(!pv->job->qsv.ctx)
                {
                    pv->job->qsv.ctx = av_mallocz(sizeof(hb_qsv_context));
                    if(!pv->job->qsv.ctx)
                    {
                        hb_error( "decavcodecvInit: qsv ctx alloc failed" );
                        return 1;
                    }
                    hb_qsv_add_context_usage(pv->job->qsv.ctx, 0);
                    pv->job->qsv.ctx->dec_space = av_mallocz(sizeof(hb_qsv_space));
                    if(!pv->job->qsv.ctx->dec_space)
                    {
                        hb_error( "decavcodecvInit: dec_space alloc failed" );
                        return 1;
                    }
                    pv->job->qsv.ctx->dec_space->is_init_done = 1;
                }
            }
        }
    }
#endif

    if( pv->job && pv->job->title && !pv->job->title->has_resolution_change )
    {
        pv->threads = HB_FFMPEG_THREADS_AUTO;
    }

#if HB_PROJECT_FEATURE_QSV
    if (pv->qsv.decode)
    {
        pv->codec = avcodec_find_decoder_by_name(pv->qsv.codec_name);
    }
    else
#endif
    {
        pv->codec = avcodec_find_decoder(w->codec_param);
    }
    if ( pv->codec == NULL )
    {
        hb_log( "decavcodecvInit: failed to find codec for id (%d)", w->codec_param );
        return 1;
    }

    pv->context = avcodec_alloc_context3( pv->codec );
    pv->context->workaround_bugs = FF_BUG_AUTODETECT;
    pv->context->err_recognition = AV_EF_CRCCHECK;
    pv->context->error_concealment = FF_EC_GUESS_MVS|FF_EC_DEBLOCK;

    if ( pv->title->opaque_priv )
    {
        AVFormatContext *ic = (AVFormatContext*)pv->title->opaque_priv;

        avcodec_parameters_to_context(pv->context,
                                  ic->streams[pv->title->video_id]->codecpar);

#if HB_PROJECT_FEATURE_QSV
        if (pv->qsv.decode &&
            pv->qsv.config.io_pattern == MFX_IOPATTERN_OUT_VIDEO_MEMORY)
        {
            // assign callbacks
            pv->context->get_format = hb_qsv_get_format;
            pv->context->get_buffer2 = hb_qsv_get_buffer;
            pv->context->hwaccel_context = 0;
        }
#endif

        // Set encoder opts
        AVDictionary * av_opts = NULL;
        av_dict_set( &av_opts, "refcounted_frames", "1", 0 );
        if (pv->title->flags & HBTF_NO_IDR)
        {
            av_dict_set( &av_opts, "flags", "output_corrupt", 0 );
        }

#if HB_PROJECT_FEATURE_QSV
        if (pv->qsv.decode && pv->context->codec_id == AV_CODEC_ID_HEVC)
        {
            av_dict_set( &av_opts, "load_plugin", "hevc_hw", 0 );
        }
#endif

        if ( hb_avcodec_open( pv->context, pv->codec, &av_opts, pv->threads ) )
        {
            av_dict_free( &av_opts );
            hb_log( "decavcodecvInit: avcodec_open failed" );
            return 1;
        }
        pv->context->pkt_timebase.num = pv->title->video_timebase.num;
        pv->context->pkt_timebase.den = pv->title->video_timebase.den;
        av_dict_free( &av_opts );

        pv->video_codec_opened = 1;
    }
    else
    {
        pv->parser = av_parser_init( w->codec_param );
    }

    pv->frame = av_frame_alloc();
    if (pv->frame == NULL)
    {
        hb_log("decavcodecvInit: av_frame_alloc failed");
        return 1;
    }

    /*
     * If not scanning, then are we supposed to extract Closed Captions
     * and send them to the decoder?
     */
    if (job != NULL && hb_list_count(job->list_subtitle) > 0)
    {
        hb_subtitle_t *subtitle;
        int i = 0;

        while ((subtitle = hb_list_item(job->list_subtitle, i++)) != NULL)
        {
            if (subtitle->source == CC608SUB &&
                subtitle->id == HB_SUBTITLE_EMBEDDED_CC_TAG)
            {
                if (pv->list_subtitle == NULL)
                {
                    pv->list_subtitle = hb_list_init();
                }
                hb_list_add(pv->list_subtitle, subtitle);
            }
        }
    }
    return 0;
}