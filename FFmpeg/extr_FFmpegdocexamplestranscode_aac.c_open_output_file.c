#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/ * sample_fmts; } ;
struct TYPE_25__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  strict_std_compliance; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; } ;
struct TYPE_24__ {int /*<<< orphan*/ * pb; TYPE_20__* oformat; int /*<<< orphan*/  url; } ;
struct TYPE_21__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_23__ {int /*<<< orphan*/  codecpar; TYPE_1__ time_base; } ;
struct TYPE_22__ {int flags; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int AVFMT_GLOBALHEADER ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_CODEC_FLAG_GLOBAL_HEADER ; 
 int /*<<< orphan*/  AV_CODEC_ID_AAC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FF_COMPLIANCE_EXPERIMENTAL ; 
 int /*<<< orphan*/  OUTPUT_BIT_RATE ; 
 int /*<<< orphan*/  OUTPUT_CHANNELS ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_get_default_channel_layout (int /*<<< orphan*/ ) ; 
 TYPE_20__* av_guess_format (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 
 TYPE_4__* avcodec_alloc_context3 (TYPE_5__*) ; 
 TYPE_5__* avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (TYPE_4__**) ; 
 int avcodec_open2 (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int avcodec_parameters_from_context (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_3__* avformat_alloc_context () ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_3__*) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ **) ; 
 int avio_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int open_output_file(const char *filename,
                            AVCodecContext *input_codec_context,
                            AVFormatContext **output_format_context,
                            AVCodecContext **output_codec_context)
{
    AVCodecContext *avctx          = NULL;
    AVIOContext *output_io_context = NULL;
    AVStream *stream               = NULL;
    AVCodec *output_codec          = NULL;
    int error;

    /* Open the output file to write to it. */
    if ((error = avio_open(&output_io_context, filename,
                           AVIO_FLAG_WRITE)) < 0) {
        fprintf(stderr, "Could not open output file '%s' (error '%s')\n",
                filename, av_err2str(error));
        return error;
    }

    /* Create a new format context for the output container format. */
    if (!(*output_format_context = avformat_alloc_context())) {
        fprintf(stderr, "Could not allocate output format context\n");
        return AVERROR(ENOMEM);
    }

    /* Associate the output file (pointer) with the container format context. */
    (*output_format_context)->pb = output_io_context;

    /* Guess the desired container format based on the file extension. */
    if (!((*output_format_context)->oformat = av_guess_format(NULL, filename,
                                                              NULL))) {
        fprintf(stderr, "Could not find output file format\n");
        goto cleanup;
    }

    if (!((*output_format_context)->url = av_strdup(filename))) {
        fprintf(stderr, "Could not allocate url.\n");
        error = AVERROR(ENOMEM);
        goto cleanup;
    }

    /* Find the encoder to be used by its name. */
    if (!(output_codec = avcodec_find_encoder(AV_CODEC_ID_AAC))) {
        fprintf(stderr, "Could not find an AAC encoder.\n");
        goto cleanup;
    }

    /* Create a new audio stream in the output file container. */
    if (!(stream = avformat_new_stream(*output_format_context, NULL))) {
        fprintf(stderr, "Could not create new stream\n");
        error = AVERROR(ENOMEM);
        goto cleanup;
    }

    avctx = avcodec_alloc_context3(output_codec);
    if (!avctx) {
        fprintf(stderr, "Could not allocate an encoding context\n");
        error = AVERROR(ENOMEM);
        goto cleanup;
    }

    /* Set the basic encoder parameters.
     * The input file's sample rate is used to avoid a sample rate conversion. */
    avctx->channels       = OUTPUT_CHANNELS;
    avctx->channel_layout = av_get_default_channel_layout(OUTPUT_CHANNELS);
    avctx->sample_rate    = input_codec_context->sample_rate;
    avctx->sample_fmt     = output_codec->sample_fmts[0];
    avctx->bit_rate       = OUTPUT_BIT_RATE;

    /* Allow the use of the experimental AAC encoder. */
    avctx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

    /* Set the sample rate for the container. */
    stream->time_base.den = input_codec_context->sample_rate;
    stream->time_base.num = 1;

    /* Some container formats (like MP4) require global headers to be present.
     * Mark the encoder so that it behaves accordingly. */
    if ((*output_format_context)->oformat->flags & AVFMT_GLOBALHEADER)
        avctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    /* Open the encoder for the audio stream to use it later. */
    if ((error = avcodec_open2(avctx, output_codec, NULL)) < 0) {
        fprintf(stderr, "Could not open output codec (error '%s')\n",
                av_err2str(error));
        goto cleanup;
    }

    error = avcodec_parameters_from_context(stream->codecpar, avctx);
    if (error < 0) {
        fprintf(stderr, "Could not initialize stream parameters\n");
        goto cleanup;
    }

    /* Save the encoder context for easier access later. */
    *output_codec_context = avctx;

    return 0;

cleanup:
    avcodec_free_context(&avctx);
    avio_closep(&(*output_format_context)->pb);
    avformat_free_context(*output_format_context);
    *output_format_context = NULL;
    return error < 0 ? error : AVERROR_EXIT;
}