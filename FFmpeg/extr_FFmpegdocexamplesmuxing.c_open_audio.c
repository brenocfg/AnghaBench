#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int sample_rate; int frame_size; int channels; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channel_layout; TYPE_1__* codec; } ;
struct TYPE_10__ {int tincr; int tincr2; int /*<<< orphan*/  swr_ctx; TYPE_2__* st; void* tmp_frame; void* frame; scalar_t__ t; TYPE_4__* enc; } ;
struct TYPE_9__ {int /*<<< orphan*/  codecpar; } ;
struct TYPE_8__ {int capabilities; } ;
typedef  TYPE_3__ OutputStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_4__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AV_CODEC_CAP_VARIABLE_FRAME_SIZE ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int M_PI ; 
 void* alloc_audio_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_opt_set_int (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set_sample_fmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avcodec_open2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avcodec_parameters_from_context (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  swr_alloc () ; 
 int swr_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void open_audio(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg)
{
    AVCodecContext *c;
    int nb_samples;
    int ret;
    AVDictionary *opt = NULL;

    c = ost->enc;

    /* open it */
    av_dict_copy(&opt, opt_arg, 0);
    ret = avcodec_open2(c, codec, &opt);
    av_dict_free(&opt);
    if (ret < 0) {
        fprintf(stderr, "Could not open audio codec: %s\n", av_err2str(ret));
        exit(1);
    }

    /* init signal generator */
    ost->t     = 0;
    ost->tincr = 2 * M_PI * 110.0 / c->sample_rate;
    /* increment frequency by 110 Hz per second */
    ost->tincr2 = 2 * M_PI * 110.0 / c->sample_rate / c->sample_rate;

    if (c->codec->capabilities & AV_CODEC_CAP_VARIABLE_FRAME_SIZE)
        nb_samples = 10000;
    else
        nb_samples = c->frame_size;

    ost->frame     = alloc_audio_frame(c->sample_fmt, c->channel_layout,
                                       c->sample_rate, nb_samples);
    ost->tmp_frame = alloc_audio_frame(AV_SAMPLE_FMT_S16, c->channel_layout,
                                       c->sample_rate, nb_samples);

    /* copy the stream parameters to the muxer */
    ret = avcodec_parameters_from_context(ost->st->codecpar, c);
    if (ret < 0) {
        fprintf(stderr, "Could not copy the stream parameters\n");
        exit(1);
    }

    /* create resampler context */
        ost->swr_ctx = swr_alloc();
        if (!ost->swr_ctx) {
            fprintf(stderr, "Could not allocate resampler context\n");
            exit(1);
        }

        /* set options */
        av_opt_set_int       (ost->swr_ctx, "in_channel_count",   c->channels,       0);
        av_opt_set_int       (ost->swr_ctx, "in_sample_rate",     c->sample_rate,    0);
        av_opt_set_sample_fmt(ost->swr_ctx, "in_sample_fmt",      AV_SAMPLE_FMT_S16, 0);
        av_opt_set_int       (ost->swr_ctx, "out_channel_count",  c->channels,       0);
        av_opt_set_int       (ost->swr_ctx, "out_sample_rate",    c->sample_rate,    0);
        av_opt_set_sample_fmt(ost->swr_ctx, "out_sample_fmt",     c->sample_fmt,     0);

        /* initialize the resampling context */
        if ((ret = swr_init(ost->swr_ctx)) < 0) {
            fprintf(stderr, "Failed to initialize the resampling context\n");
            exit(1);
        }
}